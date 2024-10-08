#!/bin/bash
# -----------------------------------------------------------------------------
# Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
# See README in the root project for more information.
# -----------------------------------------------------------------------------

# If no arguments have been given
if [ "$#" -ne 2 ]; then
    echo "ERROR: missing arguments, use as follows: $0 <ShaderFile> <Mode>" 1>&2
    exit 1
fi

# If file cannot be found
if [ ! -f "$1" ]; then
    echo "ERROR: shader file not found: $1" 1>&2
    exit 2
fi

SHADERTYPE="${1##*.}"

echo "// -----------------------------------------------------------------------------"
echo "// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.					  "
echo "// See README in the root project for more information.					  	  "
echo "// -----------------------------------------------------------------------------"
echo ""
echo "// If you wish to modify this file edit the .vert or .frag file!"
echo ""

# Include the MLX42 header
echo "#include \"MLX42/MLX42_Int.h\""
echo ""

{
    if [ "$2" -eq 1 ]; then # Output WASM specific lines
        echo "const char* ${SHADERTYPE}_shader = \"#version 300 es\\n\""
        echo "	\"precision mediump float;\""
    else # Non-Wasm, output the original shader version
        echo "const char* ${SHADERTYPE}_shader = \"$(sed -n '1{p;q;}' "$1")\\n\""
    fi

    # Read the rest of the shader file
	read
	while IFS= read -r LINE; do
		if [ ! "${LINE}" = "" ]; then
			if [ "${LINE}" = "}" ]; then
				echo "	\"${LINE}\";"
			else
				echo "	\"${LINE}\""
			fi
		fi
	done
} < "$1"

exit 0
