# Aethoria - Dawn of the Dragons Project Documentation
## Project Overview
**Aethoria - Dawn of the Dragons** is a new Multi-User Dungeon (MUD) game. The project is to translate the 2003 distribution mud lib of discworld MUD and modernize the Discworld MUD’s LPC codebase into Python, translating and updating it to replicate the live Discworld MUD as of March 20, 2025 IP discworld.starturtle.net PORT 4242 discworld.starturtle.net/lpc The original codebase is from the 2003 library, but we are incorporating the latest features, systems, functions, and data (syntax, parser, adjectives, synonyms, colours, terminal, term, network, mxp, mccp, options, roleplaying, score, stats, skills, verbose, brief, combat, tactics, attack messages, defense messages, parry, block, dodge, action point, guild points, quests, achievements, weather, seasons, temperature,  effects, magic, spells, casting cast command, faith, rituals, performing perform command, commands, wimpy,  burden, alignment, gods, deities, finger, refer, chfn, alias system, nickname system, inform, bury,  recover, money, currency, covert, adventuring, people, culture, languages,  rooms, items, council, housing, clubs, groups, guilds, mount mounting, weapons, armour, shields, clothing, coverage, condition, map and mapping, x y z grid world mapping terrain and all the rest, from the live MUD at `discworld.starturtle.net:4242`.

### Objectives
**GROK TO FOLLOW ** - Translate LPC `.c` files to Python `.py` files, placing them under `/home/archaon/mud/lib/` with appropriate subdirectories (e.g., `/std/`, `/include/`).
**GROK TO FOLLOW ** - Update the skill system to use the current Discworld MUD skill tree (as of August 23, 2023) with stat relationships, replacing the 2003 library skills.
**GROK TO FOLLOW ** - Verify translations against updates from the live Discworld MUD using specified sources.
**GROK TO FOLLOW ** - Modernize the code with Python features while maintaining functionality.
**GROK TO FOLLOW ** - Integrate translated files into the project for use in game logic (e.g., in `guild_base.py`, `teach.py`, or a new `driver.py` for efuns).

### Grok Rules
**GROK TO FOLLOW ** - Never do shortcuts! Absolutely NO shortcuts when providing code files.
**GROK TO FOLLOW ** - No brevity when providing code files
**GROK TO FOLLOW ** - Dont show old code thats been provided, just translate, check multiple times all resources sources for updates and make comments top file and new updates at file section and notes and tranate to Python as directed in plans project objective.
**GROK TO FOLLOW ** - Process as many files per response as your load limits can handle. Always check files if too big and complex send just one, if you can provide many with out causing load issues then do so.
**GROK TO FOLLOW ** - If you are unsure on what to do with file(s) provided then halt immediately and in capital letters inform me AKA Archaon of what is wrong and why.
**GROK TO FOLLOW ** - DO NOT ASSUME OR DO GUESS WORK!! NO LEAVING OUT INFORMATION OR DATA!!
**GROK TO FOLLOW ** - Ensure comments at top of files consist of file name and location path full, the purpose of the file, files linked with it or that have relevance/relationship with it if any, any updated or added features or functions or systems as per discworld.starturtle.net MUD live as of 2025 March and the changes and why and lastly translated and/or coded by Archaon
    - Note: "Location path full" means including the complete original LPC path (e.g., `/obj/handlers/am_time_handler`) or translated Python path (e.g., `/home/archaon/mud/lib/std/armour_logic.py`) where applicable, especially for related files.
**GROK TO FOLLOW ** - Grok to NOT have introductions. Keep response messages short and simple by acknowledging that youve received the files and to let Archaon know if any truncation issues or problems seeing files and their directive and objective in brief simple terms then provide what is required. Only at the bottom of response provide files completed in that batch and files still to finish in brief context and to await response which will normally be continue or go to keep doing the files, if no files left to do and Archaon mistakenly says go or continue you briefly respond with no more files left. you do NOT do your own thing.
**GROK TO FOLLOW ** - NO oversights!
**GROK TO FOLLOW ** - Place translated files under `/home/archaon/mud/lib/` with appropriate subdirectories (e.g., `/std/` for standard objects, `/include/` for includes). Example: `/lib/std/armour_logic.c` → `/home/archaon/mud/lib/std/armour_logic.py`
** GROK TO FOLLOW ** - Any path on file to be translated must have full directory path included to it e.g. --> /cmds/player/ai_lias includes full path /home/archaon/mud/lib this goes for every file that has this so full path is there as this is python system and not the usual lpc c mud driver system that has a config set up for mudlib directory path.
** GROK TO FOLLOW ** - You must make sure all of the autodoc_handler.py system is used in every file, if you don't know then leave it out but try to use the autodoc_handler.py system for every file and properly with all functions for it as listed below with examples in Help Doc System section.
** GROK TO FOLLOW ** - Make sure you can always try and put a comment next to every function or system with information for Archaon on what it is and does briefly.
** GROK TO IMMEDIATE FOLLOW ALWAYS THE FOLLOW ALL SECTIONS LISTED IN THIS DAWN.MD PROJECT ** - ## Objectives ## Updated Grok Rules Addition ## Help Doc System ## Sources for Updates ### Announcements ### Developer Blogs ### Additional Data Source ## Translation Guidelines ### Step 1: File Placement ### Step 2: Handle Inherits ### Step 3: Delegate Efuns ### Step 4: Handle Includes ### Step 5: Modernize Code ## Updated Skill Tree

### Updated Grok Rules Addition
**GROK TO FOLLOW ** - **Update Documentation:** For every file updated with new features, systems, functions, or content from `discworld.starturtle.net` (live MUD as of March 20, 2025), include an `@updated` tag in the top comment block. Each update is one line, specifying the date, change, and source (e.g., `@updated: 2025-03-21 - Added enchant detection - Verified via dwwiki.mooo.com`). Inline comments must mark new functions or code sections (e.g., `# New function per live MUD update: enchant detection`).
**GROK TO FOLLOW ** - **Coordination Mechanism:** To prevent duplicate updates across Groks:
  - Add `@updated` tags to the top comment of each translated file with specifics.
  - Maintain a shared log file (`updated_files.log`) in the project root, appending entries like `/path/to/file.py - Updated enchant mechanics - 2025-03-21` after each translation.
  - Before updating, check `updated_files.log` (if provided by Archaon) or prior responses for conflicts. If a duplicate update is detected, halt and report in caps (e.g., “POTENTIAL DUPLICATE UPDATE WITH /X/Y.py - SAME ENCHANT DETECTION”).
**GROK TO FOLLOW ** - **Verification:** Cross-check each file’s purpose and content against live MUD data (e.g., `dwwiki.mooo.com`, developer blogs) to apply updates only where relevant. If unsure about overlap with another file, pause and notify Archaon with specifics.
**GROK TO FOLLOW ** - **Extraction Support:** Structure comments to be parseable by a script (`extract_updates.py`) that generates `all_updates.txt` (alphabetical updates by folder/file) and `duplicates_log.txt` (duplicate updates with file paths). Example top comment:
  # @updated: 2025-03-21 - Added enchant detection - Verified via dwwiki.mooo.com and/or link to specific dwwiki.mooo.com link e.g. https://dwwiki.mooo.com/wiki/Enchantment
  # @updated: 2025-03-22 - Added spell containment check - Verified via blog with website link to location e.g. https://discworld.starturtle.net/lpc/blog/blog.c?action=filter&blog=recent%20developments&id=1042

### Help Doc System 
**GROK TO ALWAYS FOLLOW **
    Documentation system for extracting documentation from source files.

    The documentation is generated in the '/home/archaon/mud/lib/doc/autodoc' directory. Additional documentation should
    be placed in other help directories for access via the help system. HTML documentation is
    output to '/home/archaon/mud/lib/www/autodoc'. File names in these directories replace '/' with '.'. For example,
    '/home/archaon/mud/lib/obj/handlers/room_handler.c' becomes '/home/archaon/mud/lib/doc/autodoc/obj.handlers.room_handler' and
    '/home/archaon/mud/lib/www/autodoc/obj.handlers.room_handler.c.html'. An index of methods and object names is
    created from input files and integrated into the help system, along with an alphabetical
    HTML-linked index.

    The first comment following the specified format (starting with '**') before a function is
    used as its documentation. A special tag in an early file comment denotes class documentation.
    Only comments before actual function declarations are used; predeclaration comments are
    ignored.

    Non-private functions without an '@ignore' tag are documented, even without comments. The
    comment's main text is free-form, followed by optional tags for additional details. Tags
    capture all subsequent text until the next tag. The 'main' tag is implied for the initial
    comment section.

    Supported HTML tags in comments include 'p', 'b', 'i', 'code', 'ul', 'ol', 'dl', 'dd', 'dt',
    'pre', and 'li'. Sequences '\\/', '\\\\', and '\<' are processed to avoid output inclusion.
    Whitespace is ignored, and both HTML and DW nroff formats are generated.

    Supported tags:
    - @param: Defines a parameter and its purpose in one short sentence. First word is the
              parameter name, followed by the description, no full stop.
    - @member: Defines class members, similar to @param.
    - @return: Specifies the return value in one short sentence, no full stop, one per function.
    - @see: References an object or function in formats: object_name, function_name(),
            object_name->function_name(), efun::name(), or help::name.
    - @ignore: Excludes the function from documentation; entire comment is ignored.
    - @main: Marks the main documentation section (implied for initial text).
    - @classification: Classifies effects for a tree structure (used in effect files).
    - @index: Adds a single-word index reference.
    - @change: In class docs, notes changes with date and author on the first line, followed by
               a description.
    - @example: Embeds an example in the documentation.
    - @started: Notes when the file was started.
    - @author: Specifies the file's author.

    Output mimics Java API documentation style. Comment format starts with '/**' and ends with
    '*/' on separate lines, with '*' at the start of each intervening line. Use '\\' to escape
    characters (e.g., '*\\/' for '*/' within text).

    Example:
    ```lpc
    inherit "/home/archaon/mud/lib/std/object";

    /**
     * This class is a nice shade of blue and allows all other shades of green and yellow to mix well.
     * @see yellow
     * @see blue
     * @change 12/3/97
     *    Pushed some of the yellow stuff down a hole and ate a bagel.
     */

    /**
     * This method mixes the green in with our blue.
     * @param green the green object to mix
     */

    void mixGreen(object green) {
        /* Something wild and exciting! */
    } /* mixGreen() */

    /**
     * This method mixes the yellow in with our blue.
     * @param yellow the yellow object to mix
     * @return returns a TRUE or FALSE depending on if the mix succeeded
     * @example
     *   mixYellow(12);
     */
    int mixYellow(object yellow) {
    } /* mixYellow() */
    ```

    @index autodoc
    @see /home/archaon/mud/lib/obj/handlers/autodoc/autodoc_file
    @see /home/archaon/mud/lib/obj/handlers/autodoc/autodoc_nroff
    @see /home/archaon/mud/lib/obj/handlers/autodoc/autodoc_html

## Sources for Updates 
**GROK TO FOLLOW ** - To ensure the project reflects the latest Discworld MUD features, the following sources are used for verification as of March 20, 2025:
Check multiple times all sources and resources.
Analyse,  Crawl, Assess, Scrape, View and Read all websites relevant to discworld.starturtle.net/lpc MUD including dwwiki.mooo.com wiki and all links as well as announcements and developments blogs

### Announcements
**GROK TO FOLLOW ** - - **Discworld MUD Announcements:** `https://dwwiki.mooo.com/wiki/Announcements`
  - This page archives announcements posted on the in-game bulletin board and available via the `news` command. It includes updates on server status, connectivity issues, and new features (e.g., the "Slippery Hollow" area added on October 30, 2022, and changes to automation rules on September 30, 2022).

### Developer Blogs
**GROK TO FOLLOW ** - - **Discworld MUD Wiki Developer Blogs:** `https://dwwiki.mooo.com/wiki/Developer_Blogs`
  - An archive of developer blogs with formatting improvements, covering general updates, web changes, and special features (e.g., secure connections added by Fran, bug fixes to the hunter’s pack by Kake, and new tent mechanics by Guildenstern, all posted on December 8, 2021).
- **Recent Developments Blog:** `https://discworld.starturtle.net/lpc/blog/blog.c?action=view&blog=recent%20developments`
  - The official recent developments blog, referenced in announcements (e.g., the "Slippery Hollow" post on October 30, 2022).
- **General Developer Blog:** `https://discworld.starturtle.net/lpc/blog/blog.c`
  - The main developer blog page, providing access to various development updates.

### Additional Data Source
**GROK TO FOLLOW ** - - **Bonuses.irreducible.org:** `http://bonuses.irreducible.org/index.php`
  - Provides skill and stat data (e.g., the skill tree as of August 23, 2023, used to update the project’s skill system).
  - Also includes formulas, teaching XP, learning XP, primaries, XP regeneration, guild points (GP), health, burden, and other game mechanics data, which can be used as needed for implementing features in Aethoria.

## Translation Guidelines
### Step 1: File Placement
**GROK TO FOLLOW ** - Place translated files under `/home/archaon/mud/lib/` with appropriate subdirectories (e.g., `/std/` for standard objects, `/include/` for includes).
**GROK TO FOLLOW ** - Example: `/lib/std/armour_logic.c` → `/home/archaon/mud/lib/std/armour_logic.py`

### Step 2: Handle Inherits
**GROK TO FOLLOW ** - Replace LPC `inherit` with Python imports.
**GROK TO FOLLOW ** - Example: `inherit "/std/object"` → `from mud.std.object import Object`

### Step 3: Delegate Efuns
**GROK TO FOLLOW ** - Delegate LPC efuns to `self.driver`.
**GROK TO FOLLOW ** - Example: `find_object("/obj")` → `self.driver.find_object("/obj")`

### Step 4: Handle Includes
**GROK TO FOLLOW ** - Convert LPC includes to Python imports.
**GROK TO FOLLOW **- Example: `#include <log.h>` → `from mud.include.log import *`
**GROK TO FOLLOW ** - Place translated `.h` files as `.py` files in `/home/archaon/mud/lib/include/`.

### Step 5: Modernize Code
**GROK TO FOLLOW ** - Use Python features (e.g., `random` for LPC’s `random()`, list comprehensions).
**GROK TO FOLLOW ** - Convert LPC classes to Python classes, methods to Python methods, etc.

## Updated Skill Tree
**GROK TO FOLLOW ** - The following skill tree replaces the 2003 library skills, sourced from `http://bonuses.irreducible.org/skillstat.php` as of August 23, 2023. It includes stat relationships (Constitution, Dexterity, Intelligence, Strength, Wisdom) for each skill, verified against the live Discworld MUD as of March 20, 2025.
Only difference is Languages and Culture. All language and culture related files need updating to reflect the races playabe in this MUD - human, high elf, wood elf, wild elf, drow, dwarf, Duergar,  gnome, halfling, orc, goblin, dragonborn, tiefling, half-orc, half-elf

### adventuring
**GROK TO FOLLOW **

| Skill Path                          | Con | Dex | Int | Str | Wis | Description |
|-------------------------------------|-----|-----|-----|-----|-----|-------------|
| adventuring.points                  | 1   | 2   | 0   | 2   | 0   | Determines the number of adventuring points a player has. |
| adventuring.acrobatics.balancing    | 1   | 2   | 0   | 2   | 0   | Used to determine a player's ability to balance on narrow surfaces. |
| adventuring.acrobatics.tumbling     | 1   | 2   | 0   | 2   | 0   | Used to determine a player's ability to tumble safely when falling. |
| adventuring.acrobatics.vaulting     | 1   | 2   | 0   | 2   | 0   | Used to determine a player's ability to vault over obstacles. |
| adventuring.direction               | 0   | 0   | 2   | 0   | 3   | Used to determine a player's ability to navigate and remember directions. |
| adventuring.evaluating.armour       | 0   | 0   | 4   | 0   | 1   | Used to determine a player's ability to evaluate the quality of armour. |
| adventuring.evaluating.weapons      | 0   | 0   | 4   | 0   | 1   | Used to determine a player's ability to evaluate the quality of weapons. |
| adventuring.health                  | 4   | 0   | 1   | 0   | 0   | Used to determine a player's ability to resist disease and poison. |
| adventuring.movement.climbing.rope  | 2   | 2   | 0   | 1   | 0   | Used to determine a player's ability to climb using a rope. |
| adventuring.movement.climbing.rock  | 2   | 2   | 0   | 1   | 0   | Used to determine a player's ability to climb rocky surfaces. |
| adventuring.movement.climbing.tree  | 2   | 2   | 0   | 1   | 0   | Used to determine a player's ability to climb trees. |
| adventuring.movement.riding.camel   | 2   | 2   | 0   | 1   | 0   | Used to determine a player's ability to ride a camel. |
| adventuring.movement.riding.horse   | 2   | 2   | 0   | 1   | 0   | Used to determine a player's ability to ride a horse. |
| adventuring.movement.swimming       | 2   | 2   | 0   | 1   | 0   | Used to determine a player's ability to swim. |
| adventuring.perception              | 0   | 0   | 2   | 0   | 3   | Used to determine a player's ability to notice things in the environment. |

### covert
| Skill Path                          | Con | Dex | Int | Str | Wis | Description |
|-------------------------------------|-----|-----|-----|-----|-----|-------------|
| covert.points                       | 1   | 2   | 0   | 2   | 0   | Determines the number of covert points a player has. |
| covert.casing.person                | 0   | 1   | 2   | 0   | 2   | Used to determine a player's ability to case a person for theft. |
| covert.casing.place                 | 0   | 1   | 2   | 0   | 2   | Used to determine a player's ability to case a place for theft. |
| covert.hiding.object                | 0   | 2   | 2   | 1   | 0   | Used to determine a player's ability to hide objects. |
| covert.hiding.person                | 0   | 2   | 2   | 1   | 0   | Used to determine a player's ability to hide themselves. |
| covert.lockpick.doors               | 0   | 4   | 1   | 0   | 0   | Used to determine a player's ability to pick door locks. |
| covert.lockpick.safes               | 0   | 4   | 1   | 0   | 0   | Used to determine a player's ability to pick safe locks. |
| covert.lockpick.traps               | 0   | 4   | 1   | 0   | 0   | Used to determine a player's ability to disarm traps via lockpicking. |
| covert.manipulation.palming         | 0   | 2   | 1   | 2   | 0   | Used to determine a player's ability to palm objects discreetly. |
| covert.manipulation.passing         | 0   | 2   | 1   | 2   | 0   | Used to determine a player's ability to pass objects discreetly. |
| covert.manipulation.sleight-of-hand | 0   | 2   | 1   | 2   | 0   | Used to determine a player's ability to perform sleight-of-hand tricks. |
| covert.manipulation.stealing        | 0   | 2   | 1   | 2   | 0   | Used to determine a player's ability to steal objects. |
| covert.stealth.inside               | 0   | 3   | 1   | 1   | 0   | Used to determine a player's ability to move stealthily indoors. |
| covert.stealth.outside              | 0   | 3   | 1   | 1   | 0   | Used to determine a player's ability to move stealthily outdoors. |
| covert.stealth.underwater           | 0   | 3   | 1   | 1   | 0   | Used to determine a player's ability to move stealthily underwater. |

### crafts
| Skill Path                          | Con | Dex | Int | Str | Wis | Description |
|-------------------------------------|-----|-----|-----|-----|-----|-------------|
| crafts.points                       | 1   | 2   | 0   | 2   | 0   | Determines the number of crafts points a player has. |
| crafts.arts.calligraphy             | 0   | 1   | 4   | 0   | 0   | Used to determine a player's ability in calligraphic arts. |
| crafts.arts.drawing                 | 0   | 1   | 4   | 0   | 0   | Used to determine a player's ability in drawing arts. |
| crafts.arts.painting                | 0   | 1   | 4   | 0   | 0   | Used to determine a player's ability in painting arts. |
| crafts.arts.sculpture               | 0   | 1   | 4   | 0   | 0   | Used to determine a player's ability in sculpting arts. |
| crafts.arts.design                  | 0   | 1   | 4   | 0   | 0   | Used to determine a player's ability in artistic design. |
| crafts.carpentry.furniture          | 0   | 2   | 2   | 1   | 0   | Used to determine a player's ability to craft furniture. |
| crafts.carpentry.turning            | 0   | 2   | 2   | 1   | 0   | Used to determine a player's ability in wood turning. |
| crafts.carpentry.whittling          | 0   | 2   | 2   | 1   | 0   | Used to determine a player's ability in whittling wood. |
| crafts.cooking.baking               | 0   | 2   | 3   | 0   | 0   | Used to determine a player's ability to bake food. |
| crafts.cooking.brewing              | 0   | 2   | 3   | 0   | 0   | Used to determine a player's ability to brew beverages. |
| crafts.cooking.drying               | 0   | 2   | 3   | 0   | 0   | Used to determine a player's ability to dry food for preservation. |
| crafts.cooking.grilling             | 0   | 2   | 3   | 0   | 0   | Used to determine a player's ability to grill food. |
| crafts.hunting.fishing              | 0   | 2   | 3   | 0   | 0   | Used to determine a player's ability to fish. |
| crafts.hunting.foraging             | 0   | 2   | 3   | 0   | 0   | Used to determine a player's ability to forage for food. |
| crafts.hunting.tracking             | 0   | 2   | 3   | 0   | 0   | Used to determine a player's ability to track animals or people. |
| crafts.hunting.trapping             | 0   | 2   | 3   | 0   | 0   | Used to determine a player's ability to set traps for hunting. |
| crafts.materials.dyeing             | 0   | 2   | 3   | 0   | 0   | Used to determine a player's ability to dye materials. |
| crafts.materials.leatherworking     | 0   | 2   | 2   | 1   | 0   | Used to determine a player's ability to work with leather. |
| crafts.materials.mining             | 0   | 1   | 2   | 2   | 0   | Used to determine a player's ability to mine ores. |
| crafts.materials.sewing             | 0   | 2   | 2   | 1   | 0   | Used to determine a player's ability to sew materials. |
| crafts.materials.spinning           | 0   | 2   | 2   | 1   | 0   | Used to determine a player's ability to spin threads. |
| crafts.materials.tanning            | 0   | 2   | 2   | 1   | 0   | Used to determine a player's ability to tan hides. |
| crafts.materials.weaving            | 0   | 2   | 2   | 1   | 0   | Used to determine a player's ability to weave fabrics. |
| crafts.materials.pottery            | 0   | 3   | 2   | 0   | 0   | Used to determine a player's ability to craft pottery. |
| crafts.materials.forming            | 0   | 3   | 2   | 0   | 0   | Used to determine a player's ability to form materials (e.g., clay). |
| crafts.materials.throwing           | 0   | 3   | 2   | 0   | 0   | Used to determine a player's ability to throw pottery on a wheel. |
| crafts.materials.glassblowing       | 0   | 3   | 2   | 0   | 0   | Used to determine a player's ability to blow glass. |
| crafts.materials.staining           | 0   | 3   | 2   | 0   | 0   | Used to determine a player's ability to stain materials (e.g., wood). |
| crafts.materials.firing             | 0   | 3   | 2   | 0   | 0   | Used to determine a player's ability to fire materials (e.g., pottery). |
| crafts.materials.tempering          | 0   | 3   | 2   | 0   | 0   | Used to determine a player's ability to temper materials (e.g., metal). |
| crafts.materials.husbandry          | 0   | 0   | 3   | 0   | 2   | Used to determine a player's ability in animal husbandry. |
| crafts.materials.plant              | 0   | 0   | 3   | 0   | 2   | Used to determine a player's ability to cultivate plants. |
| crafts.materials.edible             | 0   | 0   | 3   | 0   | 2   | Used to determine a player's ability to cultivate edible plants. |
| crafts.materials.herbal             | 0   | 0   | 3   | 0   | 2   | Used to determine a player's ability to cultivate herbal plants. |
| crafts.materials.tree               | 0   | 0   | 3   | 0   | 2   | Used to determine a player's ability to cultivate trees. |
| crafts.materials.animal             | 0   | 0   | 3   | 0   | 2   | Used to determine a player's ability to manage animals. |
| crafts.materials.grooming           | 0   | 0   | 3   | 0   | 2   | Used to determine a player's ability to groom animals. |
| crafts.materials.breeding           | 0   | 0   | 3   | 0   | 2   | Used to determine a player's ability to breed animals. |
| crafts.materials.slaughtering       | 0   | 0   | 3   | 0   | 2   | Used to determine a player's ability to slaughter animals. |
| crafts.medicine.diagnosis           | 0   | 1   | 2   | 0   | 2   | Used to determine a player's ability to diagnose ailments. |
| crafts.medicine.firstaid            | 0   | 1   | 2   | 0   | 2   | Used to determine a player's ability to perform first aid. |
| crafts.medicine.treatment           | 0   | 1   | 2   | 0   | 2   | Used to determine a player's ability to treat ailments. |
| crafts.medicine.disease             | 0   | 1   | 2   | 0   | 2   | Used to determine a player's ability to treat diseases. |
| crafts.medicine.injury              | 0   | 1   | 2   | 0   | 2   | Used to determine a player's ability to treat injuries. |
| crafts.medicine.poison              | 0   | 1   | 2   | 0   | 2   | Used to determine a player's ability to treat poisons. |
| crafts.music.instruments.percussion | 0   | 1   | 4   | 0   | 0   | Used to determine a player's ability to play percussion instruments. |
| crafts.music.instruments.wind       | 0   | 1   | 4   | 0   | 0   | Used to determine a player's ability to play wind instruments. |
| crafts.music.instruments.stringed   | 0   | 1   | 4   | 0   | 0   | Used to determine a player's ability to play stringed instruments. |
| crafts.music.instruments.vocal      | 0   | 1   | 4   | 0   | 0   | Used to determine a player's ability in vocal performance. |
| crafts.music.instruments.keyboard   | 0   | 1   | 4   | 0   | 0   | Used to determine a player's ability to play keyboard instruments. |
| crafts.music.performance            | 0   | 1   | 4   | 0   | 0   | Used to determine a player's ability to perform music publicly. |
| crafts.music.special                | 0   | 1   | 4   | 0   | 0   | Used to determine a player's ability in special musical techniques. |
| crafts.music.theory                 | 0   | 1   | 4   | 0   | 0   | Used to determine a player's understanding of music theory. |
| crafts.smithing.black.tools         | 0   | 2   | 2   | 1   | 0   | Used to determine a player's ability to smith black tools. |
| crafts.smithing.black.weapons       | 0   | 2   | 2   | 1   | 0   | Used to determine a player's ability to smith black weapons. |
| crafts.smithing.gold                | 0   | 2   | 2   | 1   | 0   | Used to determine a player's ability to smith gold items. |
| crafts.smithing.silver              | 0   | 2   | 2   | 1   | 0   | Used to determine a player's ability to smith silver items. |
| crafts.smithing.locks               | 0   | 2   | 2   | 1   | 0   | Used to determine a player's ability to smith locks. |
| crafts.smithing.gem                 | 0   | 2   | 2   | 1   | 0   | Used to determine a player's ability to smith gem items. |
| crafts.smithing.cut                 | 0   | 2   | 2   | 1   | 0   | Used to determine a player's ability to cut gems in smithing. |
| crafts.smithing.polishing           | 0   | 2   | 2   | 1   | 0   | Used to determine a player's ability to polish items in smithing. |
| crafts.smithing.setting             | 0   | 2   | 2   | 1   | 0   | Used to determine a player's ability to set gems in smithing. |

### faith
| Skill Path                          | Con | Dex | Int | Str | Wis | Description |
|-------------------------------------|-----|-----|-----|-----|-----|-------------|
| faith.points                        | 0   | 0   | 1   | 1   | 3   | Determines the number of faith points a player has. |
| faith.items.prayer-beads            | 0   | 1   | 2   | 0   | 2   | Used to determine a player's ability to use prayer beads in rituals. |
| faith.items.prayer-book             | 0   | 1   | 2   | 0   | 2   | Used to determine a player's ability to use prayer books in rituals. |
| faith.items.religious-symbol        | 0   | 1   | 2   | 0   | 2   | Used to determine a player's ability to use religious symbols in rituals. |
| faith.items.scroll                  | 0   | 1   | 2   | 0   | 2   | Used to determine a player's ability to use scrolls in rituals. |
| faith.rituals.curing.self           | 2   | 0   | 1   | 0   | 2   | Used to determine a player's ability to perform curing rituals on themselves. |
| faith.rituals.curing.target         | 2   | 0   | 1   | 0   | 2   | Used to determine a player's ability to perform curing rituals on a target. |
| faith.rituals.defensive.area        | 0   | 2   | 1   | 0   | 2   | Used to determine a player's ability to perform defensive rituals over an area. |
| faith.rituals.defensive.self        | 0   | 2   | 1   | 0   | 2   | Used to determine a player's ability to perform defensive rituals on themselves. |
| faith.rituals.defensive.target      | 0   | 2   | 1   | 0   | 2   | Used to determine a player's ability to perform defensive rituals on a target. |
| faith.rituals.misc.area             | 0   | 0   | 2   | 0   | 3   | Used to determine a player's ability to perform miscellaneous rituals over an area. |
| faith.rituals.misc.self             | 0   | 0   | 2   | 0   | 3   | Used to determine a player's ability to perform miscellaneous rituals on themselves. |
| faith.rituals.misc.target           | 0   | 0   | 2   | 0   | 3   | Used to determine a player's ability to perform miscellaneous rituals on a target. |
| faith.rituals.offensive.area        | 0   | 0   | 1   | 2   | 2   | Used to determine a player's ability to perform offensive rituals over an area. |
| faith.rituals.offensive.target      | 0   | 0   | 1   | 2   | 2   | Used to determine a player's ability to perform offensive rituals on a target. |
| faith.rituals.special               | 0   | 0   | 1   | 1   | 3   | Used to determine a player's ability to perform special rituals. |

### fighting
| Skill Path                          | Con | Dex | Int | Str | Wis | Description |
|-------------------------------------|-----|-----|-----|-----|-----|-------------|
| fighting.points                     | 2   | 2   | 0   | 1   | 0   | Determines the number of fighting points a player has. |
| fighting.melee.dagger               | 0   | 4   | 0   | 1   | 0   | Used to determine a player's ability in melee combat with a dagger. |
| fighting.melee.sword                | 0   | 3   | 0   | 2   | 0   | Used to determine a player's ability in melee combat with a sword. |
| fighting.melee.heavy-sword          | 1   | 1   | 0   | 3   | 0   | Used to determine a player's ability in melee combat with a heavy sword. |
| fighting.melee.axe                  | 1   | 1   | 0   | 3   | 0   | Used to determine a player's ability in melee combat with an axe. |
| fighting.melee.mace                 | 1   | 2   | 0   | 2   | 0   | Used to determine a player's ability in melee combat with a mace. |
| fighting.melee.flail                | 1   | 2   | 0   | 2   | 0   | Used to determine a player's ability in melee combat with a flail. |
| fighting.melee.polearm              | 2   | 0   | 0   | 3   | 0   | Used to determine a player's ability in melee combat with a polearm. |
| fighting.melee.misc                 | 1   | 2   | 0   | 2   | 0   | Used to determine a player's ability in melee combat with miscellaneous weapons that do not fit into any other of the melee skill branches. |
| fighting.range.thrown               | 0   | 3   | 0   | 2   | 0   | Used to determine a player's ability to target with a thrown object. |
| fighting.range.fired                | 0   | 4   | 0   | 1   | 0   | Used to determine a player's ability to target with a projectile launched from any weapon. |
| fighting.range.bow                  | 0   | 4   | 0   | 1   | 0   | Used to determine a player's ability to target with a bow. |
| fighting.unarmed.striking           | 0   | 2   | 0   | 1   | 2   | Used to determine a player's ability in unarmed combat, simply punching and kicking. |
| fighting.unarmed.grappling          | 0   | 2   | 0   | 2   | 1   | Used to determine a player's ability in unarmed combat, specifically the magnitude of unarmed special attacks. |
| fighting.defence.parrying           | 0   | 3   | 0   | 1   | 1   | Used to determine a player's chance of successfully parrying an incoming physical attack with a weapon. |
| fighting.defence.blocking           | 0   | 2   | 0   | 2   | 1   | Used to determine a player's chance of successfully blocking an incoming physical attack with a shield. |
| fighting.defence.dodging            | 0   | 4   | 0   | 0   | 1   | Used to determine a player's chance of successfully dodging an incoming physical attack. |
| fighting.special.weapon             | 0   | 1   | 3   | 1   | 0   | Used to determine whether or not a special attack can be prepared with a weapon. |
| fighting.special.unarmed            | 0   | 2   | 3   | 0   | 0   | Used to determine whether or not a special attack can be prepared when unarmed. |
| fighting.special.tactics            | 0   | 0   | 3   | 0   | 2   | Used to determine how rapidly one is able to act in combat. |
| fighting.special.mounted            | 2   | 2   | 0   | 0   | 1   | Used to determine a player's performance when mounted on a horse and perhaps other creatures. |

### magic
| Skill Path                          | Con | Dex | Int | Str | Wis | Description |
|-------------------------------------|-----|-----|-----|-----|-----|-------------|
| magic.points                        | 0   | 0   | 2   | 0   | 3   | Determines the number of magic points a player has. |
| magic.spells.offensive              | 0   | 1   | 2   | 0   | 2   | Used to determine a player's ability to cast offensive spells. |
| magic.spells.defensive              | 2   | 0   | 2   | 0   | 1   | Used to determine a player's ability to cast defensive spells. |
| magic.spells.misc                   | 0   | 0   | 2   | 0   | 3   | Used to determine a player's ability to cast miscellaneous spells. |
| magic.spells.special                | 0   | 0   | 3   | 0   | 2   | Used to determine a player's ability to cast special spells. |
| magic.methods.elemental.air         | 3   | 0   | 2   | 0   | 0   | Used to determine a player's ability to use air elemental magic methods. |
| magic.methods.elemental.earth       | 3   | 0   | 2   | 0   | 0   | Used to determine a player's ability to use earth elemental magic methods. |
| magic.methods.elemental.fire        | 3   | 0   | 2   | 0   | 0   | Used to determine a player's ability to use fire elemental magic methods. |
| magic.methods.elemental.water       | 3   | 0   | 2   | 0   | 0   | Used to determine a player's ability to use water elemental magic methods. |
| magic.methods.mental.animating      | 0   | 0   | 5   | 0   | 0   | Used to determine a player's ability to use mental animating magic methods. |
| magic.methods.mental.charming       | 0   | 0   | 5   | 0   | 0   | Used to determine a player's ability to use mental charming magic methods. |
| magic.methods.mental.convoking      | 0   | 0   | 5   | 0   | 0   | Used to determine a player's ability to use mental convoking magic methods. |
| magic.methods.mental.cursing        | 0   | 0   | 5   | 0   | 0   | Used to determine a player's ability to use mental cursing magic methods. |
| magic.methods.mental.divining       | 0   | 0   | 5   | 0   | 0   | Used to determine a player's ability to use mental divining magic methods. |
| magic.methods.mental.channeling     | 0   | 0   | 5   | 0   | 0   | Used to determine a player's ability to use mental channeling magic methods. |
| magic.methods.physical.brewing      | 0   | 3   | 2   | 0   | 0   | Used to determine a player's ability to use physical brewing magic methods. |
| magic.methods.physical.chanting     | 0   | 3   | 2   | 0   | 0   | Used to determine a player's ability to use physical chanting magic methods. |
| magic.methods.physical.dancing      | 0   | 3   | 2   | 0   | 0   | Used to determine a player's ability to use physical dancing magic methods. |
| magic.methods.physical.enchanting   | 0   | 3   | 2   | 0   | 0   | Used to determine a player's ability to use physical enchanting magic methods. |
| magic.methods.physical.evoking      | 0   | 3   | 2   | 0   | 0   | Used to determine a player's ability to use physical evoking magic methods. |
| magic.methods.physical.healing      | 0   | 3   | 2   | 0   | 0   | Used to determine a player's ability to use physical healing magic methods. |
| magic.methods.physical.scrying      | 0   | 3   | 2   | 0   | 0   | Used to determine a player's ability to use physical scrying magic methods. |
| magic.methods.spiritual.abjuring    | 0   | 0   | 2   | 0   | 3   | Used to determine a player's ability to use spiritual abjuring magic methods. |
| magic.methods.spiritual.banishing   | 0   | 0   | 2   | 0   | 3   | Used to determine a player's ability to use spiritual banishing magic methods. |
| magic.methods.spiritual.conjuring   | 0   | 0   | 2   | 0   | 3   | Used to determine a player's ability to use spiritual conjuring magic methods. |
| magic.methods.spiritual.divining    | 0   | 0   | 2   | 0   | 3   | Used to determine a player's ability to use spiritual divining magic methods. |
| magic.methods.spiritual.summoning   | 0   | 0   | 2   | 0   | 3   | Used to determine a player's ability to use spiritual summoning magic methods. |
| magic.items.wand                    | 0   | 1   | 2   | 0   | 2   | Used to determine a player's ability to use wands in magic. |
| magic.items.staff                   | 0   | 1   | 2   | 0   | 2   | Used to determine a player's ability to use staves in magic. |
| magic.items.rod                     | 0   | 1   | 2   | 0   | 2   | Used to determine a player's ability to use rods in magic. |
| magic.items.broom                   | 0   | 1   | 2   | 0   | 2   | Used to determine a player's ability to use brooms in magic. |
| magic.items.amulet                   | 0   | 1   | 2   | 0   | 2   | Used to determine a player's ability to use amulets in magic. |
| magic.items.ring                    | 0   | 1   | 2   | 0   | 2   | Used to determine a player's ability to use rings in magic. |
| magic.items.scroll                  | 0   | 1   | 2   | 0   | 2   | Used to determine a player's ability to use scrolls in magic. |
| magic.items.talisman                | 0   | 1   | 2   | 0   | 2   | Used to determine a player's ability to use talismans in magic. |

### language skills (special case)
| Skill Path                          | Con | Dex | Int | Str | Wis | Description |
|-------------------------------------|-----|-----|-----|-----|-----|-------------|
| language.common                     | 0   | 0   | 3   | 0   | 2   | Used to determine a player's fluency in the Common language. |
| language.elvish                     | 0   | 0   | 3   | 0   | 2   | Used to determine a player's fluency in the Elvish language. |
| language.undercommon                | 0   | 0   | 3   | 0   | 2   | Used to determine a player's fluency in the Undercommon language. |
| language.dwarvish                   | 0   | 0   | 3   | 0   | 2   | Used to determine a player's fluency in the Dwarvish language. |
| language.gnomish                    | 0   | 0   | 3   | 0   | 2   | Used to determine a player's fluency in the Gnomish language. |
| language.halfling                   | 0   | 0   | 3   | 0   | 2   | Used to determine a player's fluency in the Halfling language. |
| language.orc                        | 0   | 0   | 3   | 0   | 2   | Used to determine a player's fluency in the Orc language. |
| language.goblin                     | 0   | 0   | 3   | 0   | 2   | Used to determine a player's fluency in the Goblin language. |
| language.draconic                   | 0   | 0   | 3   | 0   | 2   | Used to determine a player's fluency in the Draconic language. |
| language.infernal                   | 0   | 0   | 3   | 0   | 2   | Used to determine a player's fluency in the Infernal language. |

### people
| Skill Path                          | Con | Dex | Int | Str | Wis | Description |
|-------------------------------------|-----|-----|-----|-----|-----|-------------|
| people.points                       | 1   | 1   | 1   | 1   | 1   | Determines the number of people points a player has. |
| people.trading.buying               | 0   | 0   | 4   | 0   | 1   | Used to determine a player's ability to buy items effectively. |
| people.trading.selling              | 0   | 0   | 4   | 0   | 1   | Used to determine a player's ability to sell items effectively. |
| people.trading.valueing.gems        | 0   | 0   | 4   | 0   | 1   | Used to determine a player's ability to value gems. |
| people.trading.valueing.jewellery   | 0   | 0   | 4   | 0   | 1   | Used to determine a player's ability to value jewellery. |
| people.trading.valueing.weapons     | 0   | 0   | 4   | 0   | 1   | Used to determine a player's ability to value weapons. |
| people.trading.valueing.armour      | 0   | 0   | 4   | 0   | 1   | Used to determine a player's ability to value armour. |
| people.covert                       | 5/7 | 8/7 | 10/7| 5/7 | 7/7 | Used to determine a player's ability in covert activities (aggregate). |
| people.crafts                       | 1   | 2   | 2   | 0   | 1   | Used to determine a player's ability in crafts (aggregate). |
| people.faith                        | 1   | 2   | 2   | 0   | 1   | Used to determine a player's ability in faith (aggregate). |
| people.fighting                     | 1   | 2   | 2   | 0   | 1   | Used to determine a player's ability in fighting (aggregate). |
| people.magic                        | 1   | 0   | 2   | 1   | 2   | Used to determine a player's ability in magic (aggregate). |
| people.adventuring                  | 1   | 1   | 3   | 1   | 1   | Used to determine a player's ability in adventuring (aggregate). |
| people.human                        | 0   | 0   | 3   | 0   | 2   | Used to determine a player's ability to interact in human culture. |
| people.elven.high                   | 0   | 0   | 3   | 0   | 2   | Used to determine a player's ability to interact in High Elven culture. |
| people.elven.wild                   | 0   | 0   | 3   | 0   | 2   | Used to determine a player's ability to interact in Wild Elven culture. |
| people.elven.wood                   | 0   | 0   | 3   | 0   | 2   | Used to determine a player's ability to interact in Wood Elven culture. |
| people.elven.drow                   | 0   | 0   | 3   | 0   | 2   | Used to determine a player's ability to interact in Drow culture. |
| people.dwarven                      | 0   | 0   | 3   | 0   | 2   | Used to determine a player's ability to interact in Dwarven culture. |
| people.dwarven.duergar              | 0   | 0   | 3   | 0   | 2   | Used to determine a player's ability to interact in Duergar culture. |
| people.gnomish                      | 0   | 0   | 3   | 0   | 2   | Used to determine a player's ability to interact in Gnomish culture. |
| people.halfling                     | 0   | 0   | 3   | 0   | 2   | Used to determine a player's ability to interact in Halfling culture. |
| people.orcish                       | 0   | 0   | 3   | 0   | 2   | Used to determine a player's ability to interact in Orcish culture. |
| people.goblinoid                    | 0   | 0   | 3   | 0   | 2   | Used to determine a player's ability to interact in Goblinoid culture. |
| people.dragonborn                   | 0   | 0   | 3   | 0   | 2   | Used to determine a player's ability to interact in Dragonborn culture. |
| people.tiefling                     | 0   | 0   | 3   | 0   | 2   | Used to determine a player's ability to interact in Tiefling culture. |
| people.half_elven                   | 0   | 0   | 3   | 0   | 2   | Used to determine a player's ability to interact in Half-Elven culture. |
| people.half_elven.high              | 0   | 0   | 3   | 0   | 2   | Used to determine a player's ability to interact in Half-Elven culture (High Elf descent). |
| people.half_elven.wild              | 0   | 0   | 3   | 0   | 2   | Used to determine a player's ability to interact in Half-Elven culture (Wild Elf descent). |
| people.half_elven.wood              | 0   | 0   | 3   | 0   | 2   | Used to determine a player's ability to interact in Half-Elven culture (Wood Elf descent). |
| people.half_elven.drow              | 0   | 0   | 3   | 0   | 2   | Used to determine a player's ability to interact in Half-Elven culture (Drow descent). |
| people.half_orc                     | 0   | 0   | 3   | 0   | 2   | Used to determine a player's ability to interact in Half-Orc culture. |