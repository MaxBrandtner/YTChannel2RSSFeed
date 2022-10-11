project('YTChannel2RSSFeed','c')
PROJECT_NAME = meson.project_name()

gtkdep = dependency('gtk4')

add_project_link_arguments('-pthread', language : 'c')

gnome = import('gnome')
resources = gnome.compile_resources('resources', 'YTChannel2RSSFeed.gresource.xml')

sourcefiles = files('src/main.c', 'src/algorithms.c', 'src/ip_lookup.c', 'src/callbacks.c')

executable(PROJECT_NAME, sourcefiles, resources, dependencies: gtkdep, export_dynamic: true)
