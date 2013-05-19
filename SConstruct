# vim:filetype=python
env = Environment(CCFLAGS='-g', CC='g++');
env.Program(target='magic-cleaner',
            source=['src/main.cpp','src/neural_network.cpp','src/get_metadata.cpp','src/get_config.cpp', 'src/utils.cpp'],
            #LIBS = ['magic','libxml2'])
            LIBS = ['magic', 'boost_filesystem'])
env.ParseConfig("pkg-config --libs --cflags libxml-2.0")
#print env.Dump();
