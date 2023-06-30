#include <SDL2/SDL.h>
#include <stdbool.h>

#include "config.h"
#include "malla.h"
#include "vector.h"
#include "simulador.h"

#ifdef TTF
#include <SDL2/SDL_ttf.h>

void escribir_texto(SDL_Renderer *renderer, TTF_Font *font, const char *s, int x, int y) {
    SDL_Color color = {255, 255, 255};  // Estaría bueno si la función recibe un enumerativo con el color, ¿no?
    SDL_Surface *surface = TTF_RenderText_Solid(font, s, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = surface->w;
    rect.h = surface->h;

    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}
#endif

static void _click_izq(tipo_t que_hay_cerca, float pos[2], malla_t *malla){
	if (que_hay_cerca == NADA){
		agregar_nodo_a_malla(malla, pos, false);
	}
	if (que_hay_cerca == NODO){
		agregar_resorte_a_malla(malla, pos, pos);
	}
}

static void _dibujando_izq(tipo_t que_hay_cerca, float pos[2], malla_t *malla){
	if (que_hay_cerca == NODO){
		mover_nodo(malla, pos);
	}
}

static void _click_der(tipo_t que_hay_cerca, float pos[2], malla_t *malla){
	if (que_hay_cerca == NADA){
		if(!malla_iniciar_simulacion(malla))
			fprintf(stderr,"------error");
	}
	else malla_eliminar_elemento(malla, que_hay_cerca);
}

static void _obtener_pos(SDL_Event event, float pos[2]){
	pos[0] = event.motion.x;
    pos[1] = event.motion.y;
    vector_producto_por_escalar_ons(2, pos, (float)1/FACTOR_ESCALA);
}

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

#ifdef TTF
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("FreeSansBold.ttf", 24);
    if(font == NULL) {
        fprintf(stderr, "No pudo cargarse la tipografía\n");
        return 1;
    }
#endif

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Mono Bridge");

    int dormir = 0;

    // BEGIN código del alumno
	typedef enum estado {CONSTRUCCION,SIMULACION} estado_t;
	bool esta_dibujando = false;
	malla_t *malla = malla_crear();
	float pos[2] = {0,0};
	bool click_izq = false;
	bool click_der = false;
	tipo_t que_hay_cerca = NADA;
	estado_t estado = CONSTRUCCION;
	
	pos[0] = VENTANA_ANCHO/100;
	pos[1] = VENTANA_ALTO/100;
	agregar_nodo_a_malla(malla, pos, true);

    // END código del alumno

    unsigned int ticks = SDL_GetTicks();
    while(1) {
        if(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                break;

            // BEGIN código del alumno
            if (estado == CONSTRUCCION){
				if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                	click_izq = true;
                	_obtener_pos(event, pos);
                	if (!esta_dibujando)
                		que_hay_cerca = malla_tipo_cercano(malla, pos);
	            }
	
	            else if(event.type == SDL_MOUSEMOTION && click_izq) {
	            	click_izq = false;
	                esta_dibujando = true;
	                //esta dibujando con click izq
	                _obtener_pos(event, pos);
	                _dibujando_izq(que_hay_cerca, pos, malla);
	            }
	
	            if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT) {
	                click_der = true;
	                _obtener_pos(event, pos);
	                que_hay_cerca = malla_tipo_cercano(malla, pos);
	            }
	            
	            
	            else if(event.type == SDL_MOUSEMOTION && esta_dibujando) {
	           		//esta dibujando con click izq
	           		_obtener_pos(event, pos);
	           		_dibujando_izq(que_hay_cerca, pos, malla);
	            }
	
	            else if(event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT && click_izq) {
	                //se hizo click con el boton izq
	                if(esta_dibujando && que_hay_cerca == NODO){
	                	esta_dibujando = false;
	                	finalizar_mover_nodo(malla);
	                	que_hay_cerca = NADA;
	                }else{
	                	_click_izq(que_hay_cerca, pos, malla);
	                }
	                
	                if (que_hay_cerca == NODO){
	                	esta_dibujando = true;
	                	
	                }
	                click_izq = false;
	            }
	
	            else if(event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT && esta_dibujando) {
	                //dejó de dibujar
	                esta_dibujando = false;
	                if (que_hay_cerca == NODO){              
	                	finalizar_mover_nodo(malla);
	                	que_hay_cerca = NADA;
	                }
	            }
	
	            else if(event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_RIGHT && click_der) {
	                //se hizo click con el boton der
	                _click_der(que_hay_cerca, pos, malla);
		                click_der = false;
		            if (que_hay_cerca == NADA)
		            	estado = SIMULACION;
	            }
            
			}






            // END código del alumno

            continue;
        }
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);

        // BEGIN código del alumno
#ifdef TTF
/*
        escribir_texto(renderer, font, "Mono Bridge", 100, 20);
        char aux[100];
        sprintf(aux, "%03d, %03d", coordx, coordy);
        escribir_texto(renderer, font, aux, VENTANA_ANCHO - 100, VENTANA_ALTO - 34);
*/
#endif
		if (estado == SIMULACION)
			malla_simular(malla);
    	
		malla_graficar(renderer, malla);





        // END código del alumno

        SDL_RenderPresent(renderer);
        ticks = SDL_GetTicks() - ticks;
        fprintf(stderr, "ticks: %d\n", ticks);
        if(dormir) {
            SDL_Delay(dormir);
            dormir = 0;
        }
        else if(ticks < 1000 / JUEGO_FPS)
            SDL_Delay(1000 / JUEGO_FPS - ticks);
        ticks = SDL_GetTicks();
    }

    // BEGIN código del alumno

	malla_destruir(malla);
    //simulador_destruir(simulador);



    // END código del alumno

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

#ifdef TTF
    TTF_CloseFont(font);
    TTF_Quit();
#endif
    SDL_Quit();
    return 0;
}
