function
emit_symbol_text(u, s, small_font)
{
	var v = {type:SYMBOL, s:s, small_font:small_font};

	if (small_font) {
		v.height = SMALL_FONT_HEIGHT;
		v.depth = SMALL_FONT_DEPTH;
		v.width = SMALL_FONT_WIDTH;
	} else {
		v.height = FONT_HEIGHT;
		v.depth = FONT_DEPTH;
		v.width = FONT_WIDTH;
	}

	u.a.push(v);
}