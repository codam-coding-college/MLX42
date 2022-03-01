# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    compile_shader.py                                  :+:    :+:             #
#                                                      +:+                     #
#    By: tbruinem <tbruinem@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/17 22:35:29 by tbruinem      #+#    #+#                  #
#    Updated: 2022/03/01 13:07:23 by lde-la-h      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# Converts the given shader file to compilable C code for portability.

import sys
import os

if (len(sys.argv) != 2):
	exit(1)
file_path = sys.argv[1]

lines = [x for x in open(file_path).read().split('\n') if x]

shadertype = os.path.splitext(file_path)[1]

header = '''\
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lol.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 22:34:59 by W2wizard      #+#    #+#                 */
/*   Updated: 2022/02/17 22:34:59 by W2wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
'''

output = []
output.append(header)
output.append("// If you wish to modify this file edit the .vert or .frag file!\n")
output.append("#include \"MLX42/MLX42_Int.h\"\n")
output.append(f"const char	*g_{shadertype[1:]}_shader = \"{lines[0]}\\n\"")
output.extend(["	\"" + line + "\"" for line in lines[1:]])
output[-1] += ';'
for line in output:
	print(line)
