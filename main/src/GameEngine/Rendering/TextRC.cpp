#include "TextRC.h"

TextRC::TextRC(std::string text, TextStyle style) : text(text), style(style){
}

void TextRC::push(Sprite& parent, PixelDim pos, float rot) const{
	parent.setCursor(pos.x, pos.y);
	parent.setFont(style.font);
	parent.setTextDatum(style.datum);
	parent.setTextColor(style.color);
	parent.setTextSize(style.scale);

	parent.print(text.c_str());
}

void TextRC::setText(std::string text, TextStyle style){
	this->text = text;
	this->style = style;
}
