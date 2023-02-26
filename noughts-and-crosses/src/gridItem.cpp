#include "gridItem.h"
#include "states.h"
#include "shapeDrawer.h"
#include "colours.h"

GridItem::GridItem(int topLeftX, int topLeftY, int length) {
    mPosition = {topLeftX, topLeftY};
    mLength = length;
    mCenter = {topLeftX + length/2, topLeftY + length/2};
    mState = None;
    mSelected = {};
}

void GridItem::handleEvent(SDL_Event *e, PlayState &currentPlayer) {
    if (mState == Selected) {
        return;
    }

    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        if (x < mPosition.x
            || x > mPosition.x + mLength
            || y < mPosition.y
            || y > mPosition.y + mLength) {
            mState = None;
            return;
        }

        mSelected = currentPlayer == PlayState::Cross ? Cross : Nought;

        switch (e->type) {
            case SDL_MOUSEMOTION:
                if (mState == None) {
                    mState = Hover;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                mState = MouseDown;
                break;

            case SDL_MOUSEBUTTONUP:
                if (mState == MouseDown) {
                    mState = Selected;
                }
                break;
        }
    }
};

void GridItem::render(SDL_Renderer *renderer) {
    if (mState == None || !mSelected.has_value()) {
        return;
    }

    auto drawer = [this, &renderer](Uint8 colour) {
        if (mSelected.value() == PlayState::Nought) {
            drawNoughtForGridItem(renderer, colour);
        } else { drawCrossForGridItem(renderer, colour); };
    };

    switch (mState){
        case Hover:
            drawer(LIGHT_GREY);
            break;
        case MouseDown:
            drawer(DARK_GREY);
            break;
        case Selected:
            drawer(OFF_BLACK);
            break;
        case None:
            break;
    }
}

int GridItem::drawCrossForGridItem(SDL_Renderer *renderer, Uint8 colour) {
    return drawCross(renderer, mCenter, mLength / 2, 18, colour);
}

int GridItem::drawNoughtForGridItem(SDL_Renderer *renderer, Uint8 colour) {
    return drawNought(renderer, mCenter, mLength / 2, mLength / 2 + 15, colour);
}
