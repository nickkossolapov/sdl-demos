#include "textTexture.h"
#include "colors.h"

TextTexture::TextTexture(TTF_Font *font) {
    mFont = font;
    mTexture = nullptr;
    mHeight = 0;
    mWidth = 0;
}

TextTexture::~TextTexture() {
    free();
}

void TextTexture::free() {
    if (mTexture != nullptr) {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;
    }
}

void TextTexture::setText(SDL_Renderer *renderer, char *text, SDL_Color color) {
    free();

    SDL_Surface *textSurface = TTF_RenderText_LCD(mFont, text, color, OFF_WHITE);

    if (textSurface == nullptr) {
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textSurface);

    mWidth = textSurface->w;
    mHeight = textSurface->h;

    SDL_FreeSurface(textSurface);

    mTexture = texture;
}

void TextTexture::render(SDL_Renderer *renderer, SDL_Point topLeft) {
//    SDL_SetRenderDrawColor(renderer, OFF_BLACK.r, OFF_BLACK.g, OFF_BLACK.b, OFF_BLACK.a);

    if (mTexture != nullptr) {
        SDL_Rect messageRect = {
                topLeft.x,
                topLeft.y,
                mWidth,
                mHeight
        };

        SDL_RenderCopy(renderer, mTexture, nullptr, &messageRect);
    }
}

int TextTexture::getWidth()  {
    return mWidth;
}
