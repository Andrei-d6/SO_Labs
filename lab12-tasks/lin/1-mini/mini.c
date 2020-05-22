/**
 * SO, 2016
 * Lab #12
 *
 * Task 01 - mini.c
 * Implementing a minimal comand line file utility
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/sysmacros.h>

#include "utils.h"

/* added this */
#include <sys/mount.h>
#include <sys/types.h>
#include <dirent.h>

#define MAX_LINE_SIZE		256

const char *delim = " \t\n";
char *prompt = "so-lab12";

#define TODO2
#define TODO3
#define TODO4
#define TODO5
#define TODO6
#define TODO7


void listDir(char *dirname, int indent)
{
	DIR *dir;
	struct dirent *entry;
	int ret;

	char line[MAX_LINE_SIZE];
	memset(line, 0, MAX_LINE_SIZE);

	if (dirname == NULL)
		dirname = ".";

	dir = opendir(dirname);
	DIE(dir == NULL, "opendir");

	while ((entry = readdir(dir)) != NULL) {

		if (entry->d_type == DT_DIR) {
            char path[1024];

            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            snprintf(path, sizeof(path), "%s/%s", dirname, entry->d_name);
            printf("%*s[%s]\n", indent, "", entry->d_name);

            listDir(path, indent + 2);
        } else
        	printf("%*s- %s\n", indent, "", entry->d_name);
	}

	ret = closedir(dir);
	DIE(ret == -1,  "closedir");
}


int main(void)
{
	char line[MAX_LINE_SIZE];
	char *cmd, *arg1, *arg2, *arg3;
	int ret; /* to be used for function calls return code */

	while (1) {
		printf("<%s>", prompt);
		fflush(stdout);

		memset(line, 0, MAX_LINE_SIZE);

		if (fgets(line, sizeof(line), stdin) == NULL)
			exit(EXIT_SUCCESS);

		cmd = strtok(line, delim);
		if (!cmd)
			continue;
#ifdef DEBUG
		printf("Executing command: %s\n", cmd);
#endif
		if (strncmp(cmd, "quit", 4) == 0 || strncmp(cmd, "exit", 4) == 0)
			break;
#ifdef TODO2
		/* TODO2: implement list <device_node>
		 * Output: <c|b> <major>:<minor>
		 * e.g: list /dev/zero
		 * Output: /dev/zero: <c> 1:5
		 */
		if (strncmp(cmd, "list", 4) == 0) {
			arg1 = strtok(NULL, delim); /* device_node name */
			if (!arg1)
				continue;

			struct stat sb;
			char type;

			ret = lstat(arg1, &sb);
			DIE(ret == -1, "lstat");

			if (S_ISCHR(sb.st_mode) != 0)
				type = 'c';
			else
				type = 'b';

			printf("%s: <%c> %d:%d\n",
			       arg1, type/* type */, 
			       major(sb.st_dev)/* major */, 
			       minor(sb.st_dev)/* minor */);
		}
#endif

#ifdef TODO3
		/* TODO3: implement mount source target fs_type
		 * e.g: mount /dev/sda1 /mnt/disk2 ext3
		 */
		if (strncmp(cmd, "mount", 5) == 0) {
			arg1 = strtok(NULL, delim); /* source */
			arg2 = strtok(NULL, delim); /* target */
			arg3 = strtok(NULL, delim);/* fs_type (e.g: ext2) */
			
			ret = mount(arg1, arg2, arg3, MS_REMOUNT, NULL);
			DIE(ret == -1, "mount");
		}

		if (strncmp(cmd, "umount", 6) == 0) {
			/* TODO3: implement umount */
			arg1 = strtok(NULL, delim); /* target */

			ret = umount(arg1);
			DIE(ret == -1, "umount");
		}
#endif

#ifdef TODO4
		/* TODO4: implement symlink oldpath newpath
		 * e.g: symlink a.txt b.txt
		 */
		if (strncmp(cmd, "symlink", 7) == 0) {
			arg1 = strtok(NULL, delim); /* oldpath */
			arg2 = strtok(NULL, delim); /* newpath */

			ret = symlink(arg1, arg2);
			DIE(ret == -1, "symlink");

		}
		if (strncmp(cmd, "unlink", 6) == 0) {
			/* TODO4: implement unlink */
			arg1 = strtok(NULL, delim); /* pathname */

			ret = unlink(arg1);
			DIE(ret == -1, "unlink");
		}
#endif

#ifdef TODO5
		/* TODO5: implement mkdir pathname mode
		 * e.g: mkdir food 0777
		 */
		if (strncmp(cmd, "mkdir", 5) == 0) {
			arg1 = strtok(NULL, delim); /* pathname */

			ret = mkdir(arg1, 0777);
			DIE(ret < 0, "mkdir");

		}
		if (strncmp(cmd, "rmdir", 5) == 0) {
			/* TODO5: implement rmdir pathname */
			arg1 = strtok(NULL, delim); /* pathname */

			ret = rmdir(arg1);
			DIE(ret < 0, "rmdir");

		}
#endif

#ifdef TODO6
		/* TODO6: implement ls dirname
		 * e.g: ls ..
		 */
		if (strncmp(cmd, "ls", 2) == 0) {
			/* recursively print files starting with arg1 */
			arg1 = strtok(NULL, delim);

			listDir(arg1, 0);
		}
#endif

#ifdef TODO7
		if (strncmp(cmd, "chdir", 5) == 0) {
			/* TODO7: implement chdir <dir>
			 * e.g: chdir bar
			 */
			arg1 = strtok(NULL, delim); /* pathname */

			ret = chdir(arg1);
			DIE(ret == -1, "chdir");
		}

		if (strncmp(cmd, "pwd", 3) == 0) {
			/* TODO7: implement pwdir
			 * e.g: pwd
			 */
			/* print workding directory */
			getcwd(line, sizeof(line));
			DIE(line == NULL, "getcwd");

			printf("%s\n", line);

		}
#endif
	}

	return 0;
}
