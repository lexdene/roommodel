TEMPLATE  = subdirs
SUBDIRS = server client
unix{
	!exists( $$OUT_PWD/api/libapi.so ){
		system('cd $$OUT_PWD && ln -s ../Dlut-Game-Platform/api api')
	}
}
