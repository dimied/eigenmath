#include "app.h"

void
emit_formula(double x, double y, struct atom *p)
{
	int char_num, font_num, k;
	double d, dx, dy, h, w;

	k = OPCODE(p);
	h = HEIGHT(p);
	d = DEPTH(p);
	w = WIDTH(p);

	p = cddddr(p);

	switch (k) {

	case EMIT_SPACE:
		break;

	case EMIT_CHAR:
		font_num = VAL1(p);
		char_num = VAL2(p);
		emit_formula_char(x, y, font_num, char_num);
		break;

	case EMIT_LIST:
		p = car(p);
		while (iscons(p)) {
			emit_formula(x, y, car(p));
			x += WIDTH(car(p));
			p = cdr(p);
		}
		break;

	case EMIT_SUPERSCRIPT:
	case EMIT_SUBSCRIPT:
		dx = VAL1(p);
		dy = VAL2(p);
		p = caddr(p);
		emit_formula(x + dx, y + dy, p);
		break;

	case EMIT_SUBEXPR:
		emit_formula_delims(x, y, h, d, w, FONT_SIZE * DELIM_STROKE, ROMAN_FONT);
		dx = get_char_width(ROMAN_FONT, '(');
		emit_formula(x + dx, y, car(p));
		break;

	case EMIT_SMALL_SUBEXPR:
		emit_formula_delims(x, y, h, d, w, SMALL_FONT_SIZE * DELIM_STROKE, SMALL_ROMAN_FONT);
		dx = get_char_width(SMALL_ROMAN_FONT, '(');
		emit_formula(x + dx, y, car(p));
		break;

	case EMIT_FRACTION:
		emit_formula_fraction(x, y, h, d, w, FONT_SIZE * FRAC_STROKE, ROMAN_FONT, p);
		break;

	case EMIT_SMALL_FRACTION:
		emit_formula_fraction(x, y, h, d, w, SMALL_FONT_SIZE * FRAC_STROKE, SMALL_ROMAN_FONT, p);
		break;

	case EMIT_TABLE:
		emit_formula_delims(x, y, h, d, w, 1.2 * FONT_SIZE * DELIM_STROKE, ROMAN_FONT);
		dx = get_char_width(ROMAN_FONT, '(');
		emit_formula_table(x + dx, y - h, p);
		break;
	}
}

void
emit_formula_delims(double x, double y, double h, double d, double w, double stroke_width, int font_num)
{
	double cd, ch, cw;

	ch = get_cap_height(font_num);
	cd = get_char_depth(font_num, '(');
	cw = get_char_width(font_num, '(');

	if (h > ch || d > cd) {
		emit_formula_ldelim(x, y, h, d, cw, stroke_width);
		emit_formula_rdelim(x + w - cw, y, h, d, cw, stroke_width);
	} else {
		emit_formula_char(x, y, font_num, '(');
		emit_formula_char(x + w - cw, y, font_num, ')');
	}
}

void
emit_formula_ldelim(double x, double y, double h, double d, double w, double stroke_width)
{
	double x1, x2, y1, y2;

	x1 = round(x + 0.5 * w);
	x2 = x1 + round(0.5 * w);

	y1 = round(y - h);
	y2 = round(y + d);

	emit_formula_stroke(x1, y1, x1, y2, stroke_width); // stem stroke
	emit_formula_stroke(x1, y1, x2, y1, stroke_width); // top stroke
	emit_formula_stroke(x1, y2, x2, y2, stroke_width); // bottom stroke
}

void
emit_formula_rdelim(double x, double y, double h, double d, double w, double stroke_width)
{
	double x1, x2, y1, y2;

	x1 = round(x + 0.5 * w);
	x2 = x1 - round(0.5 * w);

	y1 = round(y - h);
	y2 = round(y + d);

	emit_formula_stroke(x1, y1, x1, y2, stroke_width); // stem stroke
	emit_formula_stroke(x1, y1, x2, y1, stroke_width); // top stroke
	emit_formula_stroke(x1, y2, x2, y2, stroke_width); // bottom stroke
}

void
emit_formula_fraction(double x, double y, double h, double d, double w, double stroke_width, int font_num, struct atom *p)
{
	double dx, dy;

	// horizontal line

	dy = get_operator_height(font_num);
	emit_formula_stroke(x, y - dy, x + w, y - dy, stroke_width);

	// numerator

	dx = (w - WIDTH(car(p))) / 2.0;
	dy = h - HEIGHT(car(p));
	emit_formula(x + dx, y - dy, car(p));

	// denominator

	p = cdr(p);
	dx = (w - WIDTH(car(p))) / 2.0;
	dy = d - DEPTH(car(p));
	emit_formula(x + dx, y + dy, car(p));
}

void
emit_formula_table(double x, double y, struct atom *p)
{
	int i, j, m, n;
	double column_width, dx, elem_width, row_depth, row_height;
	struct atom *d, *h, *w, *table;

	n = (int) VAL1(p);
	m = (int) VAL2(p);

	p = cddr(p);

	table = car(p);
	h = cadr(p);
	d = caddr(p);

	for (i = 0; i < n; i++) { // for each row

		row_height = VAL1(h);
		row_depth = VAL1(d);

		y += row_height;

		dx = 0.0;

		w = cadddr(p);

		for (j = 0; j < m; j++) { // for each column

			column_width = VAL1(w);
			elem_width = WIDTH(car(table));
			emit_formula(x + dx + (column_width - elem_width) / 2.0, y, car(table));
			dx += column_width;
			table = cdr(table);
			w = cdr(w);
		}

		y += row_depth;

		h = cdr(h);
		d = cdr(d);
	}
}

void
emit_formula_char(double x, double y, int font_num, int char_num)
{
	emit_push(DRAW_CHAR);
	emit_push(x);
	emit_push(y);
	emit_push(font_num);
	emit_push(char_num);
}

void
emit_formula_stroke(double x1, double y1, double x2, double y2, double stroke_width)
{
	emit_push(DRAW_STROKE);
	emit_push(x1);
	emit_push(y1);
	emit_push(x2);
	emit_push(y2);
	emit_push(stroke_width);
}
