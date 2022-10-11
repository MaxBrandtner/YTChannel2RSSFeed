project('YTChannel2RSSFeed','c')
PROJECT_NAME = meson.project_name()

gtkdep = dependency('gtk4')

add_project_link_arguments('-pthread', language : 'c')

gnome = import('gnome')
resources = gnome.compile_resources('resources', 'YTChannel2RSSFeed.gresource.xml')

sourcefiles = files('main.c', 'algorithms.c', 'ip_lookup.c', 'callbacks.c')

executable(PROJECT_NAME, sourcefiles, resources, dependencies: gtkdep, export_dynamic: true)
