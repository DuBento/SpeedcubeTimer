project('speedcube.gtk.timer', 'c')

gtkdep = dependency('gtk4')

gnome=import('gnome')
resources = gnome.compile_resources('resources','sct.gresource.xml')

sourcefiles=files('sct.c', 'timer.c')

executable('sct', sourcefiles, resources, dependencies: gtkdep, install: false)
