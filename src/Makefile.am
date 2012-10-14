# Automake file for Paddle Puffle

gamedatadir = $(pkgdatadir)/data

bin_PROGRAMS = figuras-sdl
figuras_sdl_SOURCES = figuras.c

figuras_sdl_CPPFLAGS = -DGAMEDATA_DIR=\"$(gamedatadir)/\" $(AM_CPPFLAGS)
figuras_sdl_CFLAGS = $(SDL_CFLAGS) $(SDL_image_CFLAGS) $(AM_CFLAGS)
figuras_sdl_LDADD = $(SDL_LIBS) $(SDL_image_LIBS)
