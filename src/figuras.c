/*
 * figuras.c
 * This file is part of Figuras SDL
 *
 * Copyright (C) 2012 - Félix Arreola Rodríguez
 *
 * Figuras SDL is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Figuras SDL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Figuras SDL; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, 
 * Boston, MA  02110-1301  USA
 */

#include <stdlib.h>
#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>

#define FPS (1000/24)

/* Enumerar las imágenes */
enum {
	IMG_TRIANGULO,
	IMG_CUADRADO,
	IMG_CIRCULO,
	
	NUM_IMAGES
};

/* Los nombres de archivo */
const char *images_names[NUM_IMAGES] = {
	GAMEDATA_DIR "images/triangulo.gif",
	GAMEDATA_DIR "images/cuadrado.gif",
	GAMEDATA_DIR "images/circulo.gif"
};

SDL_Surface *screen;

int main (int argc, char *argv[]) {
	SDL_Surface *imagen;
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf (stderr,
			"Error: No se pudo inicializar el sistema de video\n"
			"El error devuelto por SDL es:\n"
			"%s\n", SDL_GetError());
		exit (1);
	}
	
	/* Crear la pantalla de dibujado */
	int depth;

	depth = SDL_VideoModeOK (640, 480, 16, 0);
	screen = SDL_SetVideoMode (640, 480, depth, 0);
	
	if (screen == NULL) {
		fprintf (stderr,
			"Error: I could not set up video for 760x480 mode.\n"
			"The Simple DirectMedia error that occured was:\n"
			"%s\n", SDL_GetError());
		exit (1);
	}
	
	imagen = IMG_Load (images_names[IMG_CUADRADO]);
	
	fprintf (stdout, "Bitsperpixel: %i\n", imagen->format->BitsPerPixel);
	SDL_Event event;
	int paleta = 0, done = 0;
	SDL_Color colors[24];
	colors[0].r = 255;
	colors[0].g = colors[0].b = 0;
	
	colors[1].g = 255;
	colors[1].r = colors[1].b = 0;
	SDL_FillRect (screen, NULL, SDL_MapRGB (screen->format, 255, 255, 255));
	
	do {
		while (SDL_PollEvent(&event) > 0) {
			if (event.type == SDL_KEYDOWN) {
				SDL_SetPalette (imagen, SDL_LOGPAL|SDL_PHYSPAL, colors, 0, 24);
			}
			if (event.type == SDL_QUIT) done = 1;
			SDL_BlitSurface (imagen, NULL, screen, NULL);
			SDL_Flip (screen);
		}
	} while (!done);
	return 0;
}
