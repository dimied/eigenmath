function
emit_update_fraction(u)
{
	u.width = Math.max(u.num.width, u.den.width);

	if (u.small_font) {
		u.height = SMALL_X_HEIGHT + SMALL_VSPACE + u.num.depth + u.num.height;
		u.depth = -SMALL_X_HEIGHT + SMALL_VSPACE + u.den.height + u.den.depth;
		u.width += SMALL_MEDIUM_SPACE;
	} else {
		u.height = X_HEIGHT + VSPACE + u.num.depth + u.num.height;
		u.depth = -X_HEIGHT + VSPACE + u.den.height + u.den.depth;
		u.width += MEDIUM_SPACE;
	}
}
