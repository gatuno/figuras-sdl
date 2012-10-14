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
#define MAX_RECTS 32

/* Enumerar las imágenes */
enum {
	IMG_CUADRADO,
	IMG_TRIANGULO,
	IMG_CIRCULO,
	
	NUM_IMAGES
};

/* Los nombres de archivo */
const char *images_names[NUM_IMAGES] = {
	GAMEDATA_DIR "images/cuadrado.gif",
	GAMEDATA_DIR "images/triangulo.gif",
	GAMEDATA_DIR "images/circulo.gif"
};

enum {
	NONE_SELECTED = 0,
	SELECTED,
	
	NUM_STATES
};

/* Prototipos de función */
void setup (void);
void add_rect (SDL_Rect *zona);

/* Variables globales */
SDL_Surface *screen;
SDL_Surface *images[NUM_IMAGES];
int num_rects = 0;
SDL_Rect redraw_rects[MAX_RECTS];

SDL_Color paleta_cuadrado[NUM_STATES][2] = {
	{{19, 97, 210}, {0, 54, 167}},
	{{37, 115, 228}, {0, 78, 191}}
};

SDL_Color paleta_triangulo[NUM_STATES][3] = {
	{{255, 218, 47}, {255, 199, 28}, {231, 175, 14}},
	{{255, 236, 65}, {255, 218, 47}, {255, 199, 28}}
};

SDL_Color paleta_circulo[NUM_STATES][3] = {
	{{247, 118, 23}, {239, 99, 4}, {215, 75, 2}},
	{{255, 136, 41}, {247, 118, 23}, {239, 99, 4}}
};

int main (int argc, char *argv[]) {
	SDL_Event event;
	int focus = -1, done = 0;
	int posx[3] = {10, 200, 400};
	int posy[3] = {10, 200, 200};
	Uint32 background_color;
	SDL_Rect rect;
	int g;
	
	setup ();
	
	/* Generar el color de fondo */
	background_color = SDL_MapRGB (screen->format, 255, 255, 255);
	
	SDL_SetPalette (images[IMG_CUADRADO], SDL_LOGPAL|SDL_PHYSPAL, paleta_cuadrado[NONE_SELECTED], 0, 2);
	SDL_SetPalette (images[IMG_TRIANGULO], SDL_LOGPAL|SDL_PHYSPAL, paleta_triangulo[NONE_SELECTED], 0, 3);
	SDL_SetPalette (images[IMG_CIRCULO], SDL_LOGPAL|SDL_PHYSPAL, paleta_circulo[NONE_SELECTED], 0, 3);
	
	SDL_FillRect (screen, NULL, background_color);
	SDL_UpdateRect (screen, 0, 0, 0, 0);
	
	do {
		/* A la entrada de la iteración, borrar la posición de las figuras */
		for (g = 0; g < 3; g++) {
			rect.x = posx[IMG_CUADRADO + g];
			rect.y = posy[IMG_CUADRADO + g];
			rect.w = images[IMG_CUADRADO + g]->w; rect.h = images[IMG_CUADRADO + g]->h;
			
			SDL_FillRect (screen, &rect, background_color);
			add_rect (&rect);
		}
		
		while (SDL_PollEvent(&event) > 0) {
			switch (event.type) {
				case SDL_QUIT:
					/* Vamos a cerrar la aplicación */
					done = 1;
					break;
			}
		}
		
		/* Dibujar las figuras */
		for (g = 0; g < 3; g++) {
			rect.x = posx[IMG_CUADRADO + g];
			rect.y = posy[IMG_CUADRADO + g];
			rect.w = images[IMG_CUADRADO + g]->w; rect.h = images[IMG_CUADRADO + g]->h;
			
			SDL_BlitSurface (images[IMG_CUADRADO + g], NULL, screen, &rect);
			add_rect (&rect);
		}
		
		SDL_UpdateRects (screen, num_rects, redraw_rects);
		
	} while (!done);
	
	SDL_Quit ();
	return 0;
}
/* Set video mode: */
/* Mattias Engdegard <f91-men@nada.kth.se> */
SDL_Surface * set_video_mode (unsigned flags) {
	/* Prefer 16bpp, but also prefer native modes to emulated 16bpp. */

	int depth;

	depth = SDL_VideoModeOK (760, 480, 16, flags);
	return depth ? SDL_SetVideoMode (760, 480, depth, flags) : NULL;
}

void setup (void) {
	SDL_Surface *image;
	int g;
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf (stderr,
			"Error: No se pudo inicializar el sistema de video\n"
			"El error devuelto por SDL es:\n"
			"%s\n", SDL_GetError());
		exit (1);
	}
	
	/* Crear la pantalla de dibujado */
	screen = set_video_mode (0);
	
	if (screen == NULL) {
		fprintf (stderr,
			"Error: I could not set up video for 760x480 mode.\n"
			"The Simple DirectMedia error that occured was:\n"
			"%s\n", SDL_GetError());
		exit (1);
	}
	
	for (g = 0; g < NUM_IMAGES; g++) {
		image = IMG_Load (images_names[g]);
		
		if (image == NULL) {
			fprintf (stderr,
				"Error al cargar el archivo:\n"
				"%s\n"
				"El error devuelto por SDL es:\n"
				"%s\n", images_names[g], SDL_GetError());
			SDL_Quit ();
			exit (1);
		}
		
		images[g] = image;
		/* TODO: Mostrar la carga de porcentaje */
	}
}

void add_rect (SDL_Rect *zona) {
	if (num_rects < MAX_RECTS) {
		redraw_rects[num_rects] = *zona;
		num_rects++;
	}
}
