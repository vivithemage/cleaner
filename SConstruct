# vim:filetype=python
env = Environment(CCFLAGS='-g');
env.Program(target='magic-cleaner', source=['src/main.c','src/neural_network.c','src/update_check.c','src/get_metadata.c'])
env.Append(LIBS = ['magic','fann'])
