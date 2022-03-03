# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    compile_shader.sh                                  :+:    :+:             #
#                                                      +:+                     #
#    By: fbes <fbes@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2022/03/03 02:38:19 by fbes          #+#    #+#                  #
#    Updated: 2022/03/03 04:05:03 by fbes          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

if [ "$#" -ne 1 ]; then
	exit 1
fi

SHADERTYPE="${1##*.}"

echo "/* ************************************************************************** */"
echo "/*                                                                            */"
echo "/*                                                        ::::::::            */"
echo "/*   lol.c                                              :+:    :+:            */"
echo "/*                                                     +:+                    */"
echo "/*   By: W2wizard <lde-la-h@student.codam.nl>         +#+                     */"
echo "/*                                                   +#+                      */"
echo "/*   Created: 2022/02/17 22:34:59 by W2wizard      #+#    #+#                 */"
echo "/*   Updated: 2022/02/17 22:34:59 by W2wizard      ########   odam.nl         */"
echo "/*                                                                            */"
echo "/* ************************************************************************** */"
echo ""
echo "// If you wish to modify this file edit the .vert or .frag file!"
echo ""
echo "#include \"MLX42/MLX42_Int.h\""
echo ""
echo "const char	*g_${SHADERTYPE}_shader = \"$(head -n 2 $1 | sed -n 2p | tr -d '\r')\\n\""
{
	# Skip over first two lines
	read
	read
	while IFS= read -r LINE; do
		LINE=$(echo "$LINE" | tr -d '\r')
		if [ ! "${LINE}" = "" ]; then
			if [ "${LINE}" = "}" ]; then
				echo "	\"${LINE}\";"
			else
				echo "	\"${LINE}\""
			fi
		fi
	done
} < "$1"
echo ""
exit 0
