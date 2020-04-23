#include "Headers/SDL.h"
#include <iostream>
#include <vector>

#define window_width 750
#define window_height 750
#define sprite_size 25
#define fps 60

using namespace std;

void cap_framerate( Uint32 starting_tick ) {    
    if( (1000 / fps) > SDL_GetTicks() - starting_tick )
        SDL_Delay( (1000 / fps) - ( SDL_GetTicks() - starting_tick ) );
}

class Sprite {
    protected:
        int origin_x, origin_y;
        SDL_Surface *image;
        SDL_Rect rect;
        
    public:
        Sprite( Uint32 color, int x, int y, int w = 48, int h = 64 ) {
            this->image = SDL_CreateRGBSurface( 0, w, h, 32, 0, 0, 0, 0 );
            SDL_FillRect( this->image, NULL, color );
            
            this->rect = this->image->clip_rect;
            this->origin_x = this->rect.x = x;
            this->origin_y = this->rect.y = y;
        }

        void update() const {
            /// override 
        }

        void draw( SDL_Surface *destination ) {
            SDL_BlitSurface( this->image, NULL, destination, &rect );
        }

        SDL_Surface* get_image() const {
            return this->image;
        }

        bool operator==( const Sprite& other ) const {
            return ( this->image == other.get_image() );
        }

        int get_rect_x() const {
            return this->rect.x;
        }

        int get_rect_y() const {
            return this->rect.y;
        }

};

class SpriteGroup {
    private:
        vector<Sprite*> sprites;
        int sprites_size;

    public:
        SpriteGroup copy() const {
            SpriteGroup new_group;
            for ( int  i = 0; i < this->sprites_size; i++ )
                new_group.add( this->sprites[i] );

            return new_group;
        }

        void set_sprite( int i, Sprite &new_sprite ) {
            if( i < sprite_size)
                sprites[i] = &new_sprite;
        }

        void add( Sprite *sprite ) {
            sprites.push_back( sprite );
            sprites_size = sprites.size();
        }

        void remove( Sprite sprite_object ) {
            if(this->sprites_size > 0) {
                for ( int i = 0; i < this->sprites_size; i++ )
                    if( *sprites[i] == sprite_object )
                        sprites.erase( sprites.begin() + i );

                sprites_size = sprites.size();
            }
        }

        bool has( Sprite sprite_object ) const {
            for ( int i = 0; i < this->sprites_size; i++ )
                if( *sprites[i] == sprite_object )
                    return true;
                
            return false;
        }

        void update() const {
            if( !sprites.empty() ) {
                for ( int i = 0; i < this->sprites_size; i++ ) 
                    sprites[i]->update();
            }
        }

        void draw( SDL_Surface *destination ) {
            if( !sprites.empty() ) {
                for ( int i = 0; i < this->sprites_size; i++ ) 
                    sprites[i]->draw( destination );
            }
        }

        void empty() {
            this->sprites.clear();
            this->sprites_size = this->sprites.size();
        }

        int size() const {
            return this->sprites_size;
        }

        vector<Sprite*> get_sprites() {
            return this->sprites;
        }
};

class Block : public Sprite {
    public:
        Block( Uint32 color, int x, int y, int w = 48, int h = 64 ) : Sprite(color, x, y, w, h) {
            update_properties();
        }

        void update_properties() {
            origin_x = 0;
            origin_y = 0;
            set_position( rect.x, rect.y );
        }

        void set_position( int x, int y ) {
            rect.x = x - origin_x;
            rect.y = y - origin_y;
        }

        void set_image( const char filename[] = NULL ) {
            if(filename != NULL) {
                SDL_Surface *loaded_image = SDL_LoadBMP( filename );
                if(loaded_image != NULL) {
                    this->image = loaded_image;
                    
                    int old_x = this->rect.x;
                    int old_y = this->rect.y;

                    rect = image->clip_rect;

                    rect.x = old_x;
                    rect.y = old_y;

                    update_properties();
                }
            }
        }
};

int main() {   
    SDL_Init( SDL_INIT_EVERYTHING );
    
    SDL_Window *window = SDL_CreateWindow( "Monopoly", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_RESIZABLE );

    if(window == NULL) {
        cout<<"Error: "<<SDL_GetError()<<endl;
        return 0;
    }

    SDL_Surface * screen = SDL_GetWindowSurface( window );
    Uint32 white = SDL_MapRGB( screen->format, 255, 255, 255 );
    Uint32 red = SDL_MapRGB( screen->format, 255, 0, 0 );
    Uint32 green = SDL_MapRGB( screen->format, 0, 255, 0 );
    Uint32 blue = SDL_MapRGB( screen->format, 0, 0, 255 );

    Block block( red, 0, 0 );
    block.set_image("monopoly.bmp");
    Block player1 ( red, 680, 720, sprite_size, sprite_size );
    Block player2 ( green, 680, 705, sprite_size, sprite_size );
    Block player3 ( blue, 680, 690, sprite_size, sprite_size );

    SpriteGroup active_sprites;
    active_sprites.add( &block );
    active_sprites.add( &player1 );
    active_sprites.add( &player2 );
    active_sprites.add( &player3 );
    active_sprites.draw( screen );
    SDL_UpdateWindowSurface( window );

    SDL_Event event;
    bool running = true;
    Uint32 starting_tick;

    while (running) {   
        starting_tick = SDL_GetTicks();

        while (SDL_PollEvent( &event )) {
            if (event.type == SDL_QUIT) {
                running = false;
                break;
            }   
            
            const Uint8 *state = SDL_GetKeyboardState(NULL);
			
			if (state[SDL_SCANCODE_Q]) {
                Sprite* curr = active_sprites.get_sprites()[1];
                Sprite new_sprite = *(new Sprite( red, curr->get_rect_x() - 31, curr->get_rect_y(), sprite_size, sprite_size));
                active_sprites.set_sprite(1, new_sprite);
			}
			else if (state[SDL_SCANCODE_W]) {
				Sprite* curr = active_sprites.get_sprites()[2];
                Sprite new_sprite = *(new Sprite( green, curr->get_rect_x() - 31, curr->get_rect_y(), sprite_size, sprite_size));
                active_sprites.set_sprite(2, new_sprite);
			} 
            else if (state[SDL_SCANCODE_E]) {
				Sprite* curr = active_sprites.get_sprites()[3];
                Sprite new_sprite = *(new Sprite( blue, curr->get_rect_x() - 31, curr->get_rect_y(), sprite_size, sprite_size));
                active_sprites.set_sprite(3, new_sprite);
			} 
            active_sprites.draw( screen );
		    SDL_UpdateWindowSurface( window );   
        }
        cap_framerate(starting_tick);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}