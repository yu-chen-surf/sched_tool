#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sched_domain_flags {
	char *name;
	unsigned int val;
};

struct sched_domain_flags flag_map[] = {
	{ .name = "SD_BALANCE_NEWIDLE",	.val = 0x0001 },  /* Balance when about to become idle */
	{ .name = "SD_BALANCE_EXEC",	.val = 0x0002 },  /* Balance on exec */
	{ .name = "SD_BALANCE_FORK",	.val = 0x0004 }, /* Balance on fork, clone */
	{ .name = "SD_BALANCE_WAKE",	.val = 0x0008 }, /* Balance on wakeup */
	{ .name = "SD_WAKE_AFFINE",	.val = 0x0010 }, /* Wake task to waking CPU */
	{ .name = "SD_ASYM_CPUCAPACITY",	.val = 0x0020 }, /* Domain members have different CPU capacities */
	{ .name = "SD_SHARE_CPUCAPACITY",	.val = 0x0040 }, /* Domain members share CPU capacity */
	{ .name = "SD_SHARE_POWERDOMAIN",	.val = 0x0080 }, /* Domain members share power domain */
	{ .name = "SD_SHARE_PKG_RESOURCES",	.val = 0x0100 }, /* Domain members share CPU pkg resources */
	{ .name = "SD_SERIALIZE",	.val = 0x0200 },  /* Only a single load balancing instance */
	{ .name = "SD_ASYM_PACKING",	.val = 0x0400 }, /* Place busy groups earlier in the domain */
	{ .name = "SD_PREFER_SIBLING",	.val = 0x0800 }, /* Prefer to place tasks in a sibling domain */
	{ .name = "SD_OVERLAP",		.val = 0x1000 }, /* sched_domains of this level overlap */
	{ .name = "SD_NUMA",		.val = 0x2000 }, /* cross-node balancing */
};

int main(int argc, char *argv[])
{
	unsigned int input_flag,
		     input_nr_name,
		     output_flag = 0;
	int i, j, nr_map;

	if (argc < 2) {
		printf("./sched v2f flag_value\n");
		printf("./sched f2v flag_name0 flag_name1...\n");
		exit(1);
	}
	nr_map = sizeof(flag_map) / sizeof(struct sched_domain_flags);
	if (!strcmp(argv[1], "v2f")) {
		input_flag = atoi(argv[2]);
		for (i = 0; i < nr_map; i++)
			if (flag_map[i].val & input_flag)
				printf("%s ", flag_map[i].name);
	} else if (!strcmp(argv[1], "f2v")) {
		/* Exclude process name & mode */
		input_nr_name = argc - 2;
		if (input_nr_name > nr_map) {
			printf("Too many input flag names\n");
			exit(1);
		}
		/* Start from argv[2], iterate all elements in flag_map */
		for (i = 2; i <= 1 + input_nr_name; i++) {
			for (j = 0; j < nr_map; j++) {
				if (!strcmp(argv[i], flag_map[j].name)) {
					output_flag |= flag_map[j].val;
					break;
				}
			}
		}
		printf("%u", output_flag);
	} else {
		printf("The second must be either v2f or f2v\n");
		exit(1);
	}
	printf("\n");

	return 0;
}
