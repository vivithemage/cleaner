# vim:filetype=python
env = Environment(CCFLAGS='-g');
env.Program(target='magic-cleaner', source=['src/main.c','src/neural_network.c','src/get_metadata.c'], LIBS = ['magic', 'fann','libxml2'])

env.ParseConfig("pkg-config --libs --cflags libxml-2.0")
