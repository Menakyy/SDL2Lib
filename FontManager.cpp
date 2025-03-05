#include "FontManager.h"

#include "Logger.h"

FontManager::FontManager(const std::string& fontPath, int fontSize) : fontPath(fontPath), fontSize(fontSize)
{
}

void FontManager::init()
{
    font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (font == nullptr)
    {
        Logger::error(("Failed to load font: " + fontPath + " " + TTF_GetError()).c_str());
    }
}

FontManager::~FontManager()
{
    TTF_CloseFont(font);
}