#ifndef TEXTTEXTURE_H
#define TEXTTEXTURE_H

#include <SDL.h>
#include <SDL_ttf.h>

class TextTexture {
public:
    explicit TextTexture(TTF_Font *font);

    ~TextTexture();

    void free();

    void setText(SDL_Renderer *renderer, const char *text, int fontSize, SDL_Color fgColor, SDL_Color bgColor);

    void render(SDL_Renderer *renderer, SDL_Point topLeft);

    int getWidth() const;

    int getHeight() const;

private:
    int mWidth;
    int mHeight;

    TTF_Font *mFont;
    SDL_Texture *mTexture;
};

#endif //TEXTTEXTURE_H
