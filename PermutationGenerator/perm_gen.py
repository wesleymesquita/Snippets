def permutations_gen(source_str):
	i = 0
	if len(source_str) == 1:
		return [source_str]
	perms = []
	for i in range(len(source_str)):
		new_char  = source_str[i]
		sub_perms = permutations_gen(source_str[0:i] + source_str[i+1:])
		for sub in sub_perms:
			perms.append(new_char + sub)
	return perms		
