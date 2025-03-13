# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/project_management.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def catch_status_change(self, string, int) -> None:
            class file_access_cache {
            string id
            mapping accesses


    def save_file(self, ) -> None:
            if (find_call_out ("do_save") == -1) {
            call_out ("do_save", 10)


    def do_log(self, text: str) -> None:
            log_file (PROJECT_LOG, text)


    def do_save(self, ) -> None:
            seteuid ("Root")
            touched = 1
            unguarded ((: save_object, PROJECT_SAVE :))
            touched = 0


    def do_load(self, ) -> None:
            unguarded ((: restore_object, PROJECT_SAVE :))


    def __init__(self):
            self.string creators = []
            self.last_summary = time()


    def touch_project(self, id: str, reason: str, name: str) -> None:
            int i = find_project (id)
            object ob
            if (i == -1) {
            return


    def do_inform(self, ) -> None:
            int i
            foreach (string id, string *names in inform) {
            i = find_project (id)
            user_event ("inform", sprintf ("%s: Project %s touched by %s",
            query_multiple_short(map (projects[i]->domains, (: capitalize ($1) :))),
            id, query_multiple_short (map (uniq_array (names),
            (: capitalize ($1) :)))), "message", this_player())


    def query_touched(self, id: str) -> str:
            int i = find_project (id)
            if (i == -1) {
            return 0


    def query_last_summary(self, ) -> int:
            return last_summary


    def query_summary_page(self, ) -> str:
            string ret = "Project changes since " + ctime (last_summary) + "\n\n"
            foreach (string proj, string *names in summary) {
            ret += sprintf ("%-30s touched by %s\n",
            proj, query_multiple_short (uniq_array (names)))


    def insert_into_projects(self, temp: Any) -> int:
            int index = 0
            if (!sizeof (projects)) {
            projects = [temp]
            return 0


    def insert_into_cache(self, temp: Any) -> int:
            int index = 0
            if (!sizeof (cache)) {
            cache = [temp]
            return 0


    def insert_into_tasks(self, i: int, temp: Any) -> int:
            int index = 0
            if (!sizeof (projects[i]->tasks)) {
            projects[i]->tasks = [temp]
            return 0


    def insert_into_notes(self, i: int, temp: Any) -> int:
            int index = 0
            if (!sizeof (projects[i]->notes)) {
            projects[i]->notes = [temp]
            return 0


    def parse_details(self, project: Any) -> str:
            string ret = sprintf ("$I$5=The %s (%s) project belongs to the %s %s and is "
            "in %s, with assigned creators of: %s.\n",
            p->id, p->name, query_multiple_short (p->domains),
            (sizeof (p->domains) == 1 ? "domain" : "domains"), STATUS[p->status],
            query_multiple_short (p->creators))
            ret = replace (ret, ({"$I$5=", "<p>"}))
            return ret


    def find_project(self, id: str) -> int:
            int i = find_index (id, projects)
            return i


    def find_note(self, i: Any, id: str) -> int:
            int j
            if (!intp(i)) {
            i = find_project (i)


    def find_task(self, i: Any, id: str) -> int:
            int j
            if (!intp(i)) {
            i = find_project (i)


    def find_cache_file(self, file: str) -> int:
            int i = find_index (file, cache)
            return i


    def delete_project(self, id: str, name: str) -> int:
            int i = find_index (id, projects)
            if (i == -1) {
            return 0


    def delete_task(self, id: str, task_id: str, name: str) -> int:
            int i = find_project (id)
            int j
            if (i == -1) {
            return 0


    def delete_note(self, id: str, note_id: str, name: str) -> int:
            int i = find_project (id)
            int j
            if (i == -1) {
            return 0


    def add_cache_file(self, id: str) -> int:
            int i
            class file_access_cache tmp
            if (find_cache_file (id) != -1) {
            return -1


    def set_completion_date(self, id: str, date: int) -> int:
            int i = find_project (id)
            if (i == -1) {
            return 0


    def add_creator(self, id: str, creator: str) -> int:
            int i = find_project (id)
            if (i == -1) {
            return 0


    def add_twiki(self, id: str, twiki: str) -> int:
            int i = find_project (id)
            if (i == -1) {
            return 0


    def add_file(self, id: str, file: str, access: int, name: str, task: str) -> int:
            int i = find_project (id)
            int k
            mixed ob
            class file tmp
            class file *files = [})
            if (i == -1) {
            return 0


    def remove_file(self, id: str, file: str, task: str, name: str) -> int:
            int i = find_project (id)
            class file *tmp = [})
            if (i == -1) {
            return 0


    def reset_files(self, id: str) -> int:
            int i = find_project (id)
            projects[i]->files = [})


    def add_domain(self, id: str, domain: str) -> int:
            int i = find_project (id)
            if (i == -1) {
            return 0


    def set_project_leader(self, id: str, leader: str) -> int:
            int i = find_project (id)
            if (i == -1) {
            return 0


    def query_project_leader(self, id: str) -> str:
            int i = find_project (id)
            if (i == -1) {
            return 0


    def set_status(self, id: str, stat: int) -> int:
            int i = find_project (id)
            if (i == -1) {
            return 0


    def query_status(self, id: str) -> int:
            int i = find_project (id)
            if (i == -1) {
            return 0


    def query_all_projects_info(self, ) -> str:
            string ret = ""
            foreach (class project p in projects) {
            ret += parse_details (p)


    def set_description(self, id: str, desc: str) -> int:
            int i = find_project (id)
            if (i == -1) {
            return 0


    def query_description(self, id: str) -> str:
            int i = find_project (id)
            if (i == -1) {
            return 0


    def set_status_change(self, id: str, time: int) -> int:
            int i = find_project (id)
            if (time) {
            projects[i]->last_status_change = time


    def project_info(self, id: str) -> str:
            int i = find_project (id)
            string ret = ""
            if (i == -1) {
            return "There is no project with that ID.\n"


    def task_info(self, id: str, task_id: str) -> str:
            int i = find_project (id)
            int j
            string ret = ""
            if (i == -1) {
            return "There is no project with that ID.\n"


    def set_project_completeness(self, id: str, percent: int) -> int:
            int i = find_project (id)
            if (i == -1) {
            return -1


    def set_project_name(self, id: str, name: str) -> int:
            int i = find_project (id)
            if (i == -1) {
            return 0


    def query_project_name(self, id: str) -> str:
            int i = find_project (id)
            if (i == -1) {
            return 0


    def query_project_completeness(self, id: str) -> int:
            int i = find_project(id)
            int percent = 0
            int counter = 0
            string p
            if (i == -1) {
            return 0


    def update_project_task_completeness(self, id: str, task: str, percent: int) -> int:
            int i = find_project (id)
            int j
            if (i == -1) {
            return -1


    def assign_project_task_creator(self, id: str, task: str, creator: str) -> int:
            int i = find_project (id)
            int j
            string *cres
            if (i == -1) {
            return -1


    def add_task_to_project(self, id: str, task_id: str, name: str, aim: str) -> int:
            int i = find_project (id)
            int j
            class task tmp
            if (i == -1) {
            return 0


    def add_note_to_project(self, id: str, note_id: str, note: str, name: str) -> int:
            int i = find_project (id)
            int j
            class note tmp
            if (i == -1) {
            return 0


    def set_task_name(self, id: str, task_id: str, name: str) -> int:
            int i = find_project (id)
            int j
            if (i == -1) {
            return 0


    def set_task_aims(self, id: str, task_id: str, aims: str) -> int:
            int i = find_project (id)
            int j
            if (i == -1) {
            return 0


    def query_task_aims(self, id: str, task_id: str) -> str:
            int i = find_project (id)
            int j
            if (i == -1) {
            return 0


    def query_task_name(self, id: str, task_id: str) -> str:
            int i = find_project (id)
            int j
            if (i == -1) {
            return 0


    def set_task_comments(self, id: str, task_id: str, comments: str) -> int:
            int i = find_project (id)
            int j
            if (i == -1) {
            return 0


    def query_task_comments(self, id: str, task_id: str) -> str:
            int i = find_project (id)
            int j
            if (i == -1) {
            return 0


    def add_task_creator(self, id: str, task_id: str, creator: str) -> int:
            int i = find_project (id)
            int j
            if (i == -1) {
            return 0


    def set_task_completion(self, id: str, task_id: str, percent: int) -> int:
            int i = find_project (id)
            int j
            if (i == -1) {
            return 0


    def query_task_competion(self, id: str, task_id: str) -> int:
            int i = find_project (id)
            int j
            if (i == -1) {
            return 0


    def set_task_completion_date(self, id: str, task_id: str, date: int) -> int:
            int i = find_project (id)
            int j
            if (i == -1) {
            return 0


    def query_task_completion_date(self, id: str, task_id: str) -> int:
            int i = find_project (id)
            int j
            if (i == -1) {
            return 0


    def set_project_file(self, id: str, project: Any, name: str) -> None:
            int i = find_project (id)
            if (i == -1) {
            return 0


    def set_task_file(self, id: str, t: str, task: Any, name: str) -> None:
            int i = find_project (id)
            int j
            if (i == -1) {
            return 0


    def set_note_file(self, id: str, t: str, note: Any, name: str) -> None:
            int i = find_project (id)
            int j
            if (i == -1) {
            return 0


    def is_creator_on_project(self, name: str, id: str) -> int:
            int i = find_project (id)
            if (i == -1) {
            return 0


    def catch_status_change(self, id: str, status: int) -> None:
            object ob
            int i = find_project (id)
            foreach (string d in projects[i]->domains) {
            ob = load_object ("/d/" + d + "/master")
            if (!ob) {
            continue


    def assign_playtesters(self, id: str, pt: str, name: str) -> int:
            int i = find_project (id)
            if (i == -1) {
            return 0


    def remove_playtester(self, id: str, pt: str) -> int:
            int i = find_project (id)
            if (i == -1) {
            return 0


    def do_load_tmp(self, ) -> None:
            unguarded ((: restore_object, TMP_SAVE :))


    def do_setup(self, ) -> None:
            projects = [})
            foreach (class project p in tmp_projects) {
            projects += [p]


    def clear_file_cache(self, nfile: str) -> int:
            int i = find_cache_file (nfile)
            if (i == -1) {
            return 0


    def query_permission(self, project: str, name: str, nfile: str, access: int) -> int:
            int i = find_project (project)
            int j
            string *tasks = [})
            class file *tmp = [})
            if (i == -1) {
            return 0


    def nuke_creator_project_cache(self, creators: str) -> int:
            if (!creator_project_cache) {
            return 0


    def query_file_permission(self, name: str, nfile: str, access: int) -> int:
            string *a_projects = query_projects_for_creator (name)
            int i, j, k, l = 0
            if (!sizeof (a_projects)) {
            return 0


    def set_project_lock(self, project: str) -> None:
            project_locks[project] = time()


    def query_project_lock(self, project: str) -> int:
            if (project_locks[project] + PROJECT_LOCK > time()) {
            return 1


    def generate_pt_report(self, ) -> str:
            string *new_cache = [})
            string missing_projects = ""
            string ret = ""
            string *det = [})
            string project_list = ""
            string tmp
            string post = ""
            int i
            class project *in_pt = [})
            class project *out_pt = [})
            class project *new_pt = [})
            string *del = [})
            class project *playtesting = filter_by_query ((["status": "playtesting"]))
            foreach (class project p in playtesting) {
            new_cache += [p->id]
            if (member_array (p->id, pt_post_cache) == -1) {
            new_pt += [p]


    def make_post(self, ) -> int:
            int ret
            ret = BOARD_HAND->add_message("ptforum",
            "The Project Tracker", "What's in Playtesting?",
            generate_pt_report() +
            TWIKI_HANDLER.find_changes_in_database("Playtesters", last_summary))
            last_summary = time()
            save_file()


    def query_number_of_pts(self, proj: Any) -> int:
            int i
            int t
            if (!intp (proj)) {
            i = find_project (proj)


    def next_rotation_time(self, proj: Any) -> int:
            int i, t
            if (!intp (proj)) {
            i = find_project (proj)


    def query_time_to_rotate(self, proj: Any) -> int:
            int i
            i = next_rotation_time(proj)
            if (i < time()) {
            return 1


    def query_number_rotations(self, proj: Any) -> int:
            int i
            if (!intp (proj)) {
            i = find_project (proj)


    def query_rotation(self, proj: Any) -> int:
            int i = (!intp (proj) ? find_project (proj) : proj)
            if (i == -1) {
            return 0


    def set_complexity(self, proj: Any, com: int) -> int:
            int i = (!intp (proj) ? find_project (proj) : proj)
            if (i == -1) {
            return 0


    def set_size(self, proj: Any, siz: int) -> int:
            int i = (!intp (proj) ? find_project (proj) : proj)
            if (i == -1) {
            return 0


    def query_size(self, proj: Any) -> int:
            int i = (!intp (proj) ? find_project (proj) : proj)
            if (i == -1) {
            return 0


    def set_guild_specific(self, proj: Any, guilds: str) -> int:
            int i = (!intp (proj) ? find_project (proj) : proj)
            if (i == -1) {
            return 0


    def clear_playtesting_projects(self, names: str) -> int:
            foreach (string v in names) {
            if (pt_assignment_cache[v]) {
            map_delete (pt_assignment_cache, v)


    def set_rotations(self, proj: str, rot: int) -> None:
            int i = find_project (proj)
            if (i == -1) {
            return


    def rotate_project(self, tmp: Any) -> None:
            int i
            if (intp (tmp)) {
            i = tmp


    def reset(self, ) -> None:
            if (!last_summary) {
            last_summary = time()


    def do_mail(self, playtesters: str, proj: Any) -> None:
            string text = "Hello!\n\nYou have been assigned to project " +
            proj + " on its latest rotation.  You can use "
            "'playtesting details " + proj + " to find out more about "
            "the project if neccessary.\n\nRegards,\nThe Playtester Wheel "
            "Of Fate.\n"
            AUTO_MAILER->auto_mail( "drakkos", "The Playtester Wheel Of Fate",
            "Your new playtester assignment", implode (playtesters, ","),
            text, 0, 0, 1 )


    def clear(self, ) -> None:
            string *names
            for (int i = 0; i < sizeof (projects); i++) {
            projects[i]->all_pts = [})
            projects[i]->last_pt_cohort = [})
            projects[i]->playtesters = [})


    def test_num(self, ) -> None:
            printf ("%O\n", pt_assignment_cache)



class Project_management(MudObject):

    string creators = '[]'

    last_summary = 'time()'
