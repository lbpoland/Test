import os
import re
from typing import Dict, List, Optional
import shutil
import logging
from datetime import datetime

class DWFluffosLPCToPythonConverter:
    def __init__(self, input_dir: str = "/mnt/home2/test/Test/dw_fluffos_v3/lib/", output_dir: str = "./converted_dw_lib"):
        self.input_dir = input_dir
        self.output_dir = output_dir
        self.log_file = os.path.join(self.output_dir, "conversion_log.txt")
        self.converted_files = 0
        self.current_method = ""  # Now a class-level variable
        
        # Ensure output directory exists before logging setup
        os.makedirs(self.output_dir, exist_ok=True)

        # Setup logging after directory creation
        logging.basicConfig(filename=self.log_file, level=logging.INFO, 
                           format="%(asctime)s - %(levelname)s - %(message)s")
        logging.info("Starting LPC to Python conversion for Discworld FluffOS v3 library")

        # Forgotten Realms theming
        self.fr_theming = {
            "Ankh-Morpork": "Waterdeep",
            "Disc": "Faerûn",
            "guild": "class",
            "group": "party",
            "breaks!": "shatters under Mystra’s gaze!",
            "worn": "donned in Faerûn",
            "unworn": "cast aside in the Realms",
            "morphological field": "Mystra’s weave"
        }

        # Map LPC parent files to Python classes (simplified for common cases)
        self.inherit_map = {
            "basic/condition": "CombatHandler.Armour",
            "armour_logic": "CombatHandler.Armour",
            "living": "MudObject",
            "object": "MudObject",
            "room": "Room",
            "container": "Inventory"
        }

    def convert_all(self):
        """Convert all LPC files in the input directory to Python."""
        if not os.path.exists(self.input_dir):
            error_msg = f"Input directory {self.input_dir} not found!"
            logging.error(error_msg)
            print(error_msg)
            return

        # Clear and recreate output directory (already created in __init__, but ensure clean slate)
        if os.path.exists(self.output_dir):
            shutil.rmtree(self.output_dir)
        os.makedirs(self.output_dir)

        for root, _, files in os.walk(self.input_dir):
            for filename in files:
                if filename.endswith(".c"):
                    filepath = os.path.join(root, filename)
                    self._convert_file(filepath, filename, root)
        
        logging.info(f"Conversion complete! Processed {self.converted_files} files.")
        print(f"Conversion done! {self.converted_files} files processed. Check {self.output_dir} for Python files and {self.log_file} for details.")

    def _convert_file(self, filepath: str, filename: str, root: str):
        """Convert a single LPC file to Python."""
        try:
            with open(filepath, "r") as f:
                content = f.read()
        except Exception as e:
            logging.error(f"Failed to read {filepath}: {str(e)}")
            return

        relative_path = os.path.relpath(root, self.input_dir)
        output_subdir = os.path.join(self.output_dir, relative_path)
        os.makedirs(output_subdir, exist_ok=True)
        output_filename = filename.replace(".c", ".py")
        output_path = os.path.join(output_subdir, output_filename)

        python_code = self._translate_lpc_to_python(filename, content, root)
        try:
            with open(output_path, "w") as f:
                f.write(python_code)
            self.converted_files += 1
            logging.info(f"Converted {filepath} to {output_path}")
        except Exception as e:
            logging.error(f"Failed to write {output_path}: {str(e)}")

    def _translate_lpc_to_python(self, filename: str, content: str, root: str) -> str:
        """Translate LPC content to Python with 2025 updates and FR theming."""
        lines = content.splitlines()
        class_name = filename.replace(".c", "").capitalize()
        output = [
            f"# Generated from {root}/{filename} (2003 FluffOS v3) for Forgotten Realms MUD",
            f"# Date: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}",
            "from typing import Dict, List, Optional, Any",
            "from ..driver import MudObject, Player, driver",
            "import asyncio",
            ""
        ]

        # Detect inheritance
        inherits = re.findall(r'inherit\s+"([^"]+)"', content)
        parent_class = "MudObject"  # Default
        if inherits:
            parent = inherits[0].split("/")[-1].replace(".c", "")
            parent_class = self.inherit_map.get(parent, "MudObject")

        # State variables
        in_create = False
        method_lines = []
        self.current_method = ""  # Reset for each file
        class_attrs = {}
        imports = set(["from ..driver import MudObject, Player, driver"])

        for line in lines:
            line = line.strip()

            # Skip includes (map to imports if critical)
            if line.startswith("#include"):
                if "clothing.h" in line:
                    imports.add("from .utilities import CLOTHING_HANDLER")
                elif "armoury.h" in line:
                    imports.add("from .combat import combat_handler")
                continue

            # Handle create() function
            if "void create()" in line:
                in_create = True
                method_lines = ["def __init__(self):\n"]
                continue
            if in_create and line == "}":
                in_create = False
                output.append("    " + "    ".join(method_lines) + "\n")
                continue
            if in_create:
                if "nosave" in line:
                    continue
                if "=" in line and not line.startswith("if"):
                    var, val = line.split("=", 1)
                    var = var.strip().replace("private ", "").replace("*", "")
                    val = val.strip().rstrip(";")
                    if val.startswith("({"):
                        val = self._lpc_array_to_python_list(val)
                    elif val.isdigit():
                        val = int(val)
                    class_attrs[var] = val
                    method_lines.append(f"        self.{var} = {val}\n")
                continue

            # Handle method definitions
            match = re.match(r"(int|string|mixed|void|object\*?|int\*?)\s+(\w+)\s*\((.*)\)", line)
            if match:
                return_type, method_name, args = match.groups()
                self.current_method = method_name
                is_async = method_name in ["query_ac", "wear_armour", "set_hold", "do_damage"]  # 2025 async
                args = self._lpc_args_to_python(args)
                method_lines = [f"{'async ' if is_async else ''}def {method_name}(self, {args}) -> {self._map_return_type(return_type)}:\n"]
                if is_async:
                    imports.add("import asyncio")
                continue
            if line == "}" and self.current_method:
                output.append("    " + "    ".join(method_lines) + "\n")
                self.current_method = ""
                method_lines = []
                continue
            if self.current_method:
                line = self._translate_lpc_line(line, filename)
                if line:
                    method_lines.append(f"        {line}\n")

        # Construct class
        output[3:3] = sorted(list(imports))  # Add imports
        output.append(f"\nclass {class_name}({parent_class}):\n")
        for attr, val in class_attrs.items():
            output.append(f"    {attr} = {repr(val)}\n")
        if "weather" in filename or "query_ac" in content:
            output[3:3] = ["from .environment import weather_handler"]

        return "\n".join(output)

    def _lpc_array_to_python_list(self, lpc_array: str) -> str:
        """Convert LPC array to Python list."""
        items = lpc_array.strip("({})").split(",")
        items = [item.strip().strip('"') for item in items if item.strip()]
        return f"[{', '.join(repr(item) for item in items)}]"

    def _lpc_args_to_python(self, args: str) -> str:
        """Convert LPC args to Python typed args."""
        if not args:
            return ""
        args_list = []
        for arg in args.split(","):
            arg = arg.strip()
            if not arg:
                continue
            parts = arg.split()
            if len(parts) == 1:
                args_list.append(f"{parts[0]}")
            else:
                type_, name = parts[0], parts[1].replace("*", "")
                py_type = {"int": "int", "string": "str", "mixed": "Any", "object": "MudObject", "void": "None"}.get(type_, "Any")
                args_list.append(f"{name}: {py_type}")
        return ", ".join(args_list)

    def _map_return_type(self, lpc_type: str) -> str:
        """Map LPC return type to Python."""
        return {"int": "int", "string": "str", "mixed": "Any", "void": "None", "object": "MudObject", "object*": "List[MudObject]", "int*": "List[int]"}.get(lpc_type, "Any")

    def _translate_lpc_line(self, line: str, filename: str) -> str:
        """Translate an LPC line to Python with 2025 updates and FR theming."""
        line = line.rstrip(";").strip()
        if not line or line == "}":
            return ""

        # LPC to Python translations
        line = line.replace("this_object()", "self")
        line = re.sub(r"(\w+)\->(\w+)\((.*?)\)", r"\1.\2(\3)", line)
        line = re.sub(r"call_other\((.*?),\s*\"(\w+)\"\s*(?:,\s*(.*))?\)", r"\1.\2(\3)" if "{3}" else r"\1.\2()", line)
        line = line.replace("({ ", "[").replace(" })", "]")
        line = re.sub(r"member_array\((.*?),\s*(.*?)\)", r"\2.index(\1) if \1 in \2 else -1", line)
        line = line.replace("call_out(", "asyncio.create_task(self.")
        line = re.sub(r"tell_object\((.*?),\s*(.*?)\)", r"await \1.send(\2)", line)
        line = re.sub(r"tell_room\((.*?),\s*(.*?),\s*(.*?)\)", r"await driver.tell_room(\1, \2, exclude=\3)", line)

        # FR theming
        for discworld, fr in self.fr_theming.items():
            line = line.replace(discworld, fr)

        # 2025 updates
        if self.current_method == "query_ac":
            line += "\n        # 2025 weather effect\n        if hasattr(self, 'worn_by') and weather_handler.query_weather(self.worn_by.location) == 'rain' and 'fire' in damage_type:\n            return ac + 5"
        if self.current_method == "do_damage":
            line += "\n        # 2025 enchantment resistance\n        if hasattr(self, 'attrs') and self.attrs.get('enchantment', 0) > 0:\n            amount = max(0, amount - self.attrs['enchantment'])"

        return line

# Run the converter
if __name__ == "__main__":
    converter = DWFluffosLPCToPythonConverter()
    try:
        converter.convert_all()
    except Exception as e:
        logging.error(f"Conversion failed: {str(e)}")
        print(f"Error occurred: {str(e)}. Check {converter.log_file} for details.")
