bash -c 'python3 -c "import sys;import os;[print(x) for x in sorted(sys.path)]" | grep "$(pkg-config --variable=libdir python3 | xargs realpath)"' | head -n 1
ls  | grep -Ev '^(site-packages|test|unittest|turtledemo|tkinter|xml|venv|distutils|idlelib|ensurepip|lib2to3|config-3)' | zip -r --exclude \*.pyc --exclude __pycache__  -@ ../python37.zip
