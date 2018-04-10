#!/bin/bash
# Compile generator and validator script
python3 -c "from common import compile_gen; compile_gen()"
python3 -c "from common import compile_validator; compile_validator()"