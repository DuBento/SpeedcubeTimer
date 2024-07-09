speedcubetimer_sources = [
  'main.c',
  'speedcubetimer-application.c',
  'timer.c',
  'speedcubetimer-window.c',
]

speedcubetimer_deps = [
  dependency('gtk4'),
  dependency('libadwaita-1', version: '>= 1.4'),
]

speedcubetimer_sources += gnome.compile_resources(
  'speedcubetimer-resources',
  'speedcubetimer.gresource.xml',
  c_name: 'speedcubetimer',
)

executable(
  'speedcubetimer',
  speedcubetimer_sources,
  dependencies: speedcubetimer_deps,
  install: true,
)