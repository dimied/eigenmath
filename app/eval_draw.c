#include "app.h"

#define F p3
#define T p4
#define X p5
#define Y p6
#define XT p7
#define YT p8

void
eval_draw(void)
{
	if (drawing) {
		push_symbol(NIL);
		return;
	}

	drawing = 1;

	F = cadr(p1); // 1st arg

	T = caddr(p1); // 2nd arg

	if (T == symbol(NIL))
		T = symbol(SYMBOL_X);

	save_binding(T); // save binding of 2nd arg

	eval_draw_nib();

	restore_binding(T); // restore binding of 2nd arg

	push_symbol(NIL); // draw returns nil

	drawing = 0;
}

void
eval_draw_nib(void)
{
	setup_trange();

	setup_xrange();

	setup_yrange();

	check_for_parametric_draw();

	draw_count = 0;

	draw_pass1();
	draw_pass2();

	emit_graph();
}

void
check_for_parametric_draw(void)
{
	eval_func_arg(tmin);
	p1 = pop();

	if (istensor(p1))
		return;

	tmin = xmin;
	tmax = xmax;
}

void
draw_pass1(void)
{
	int i;
	double t;

	for (i = 0; i <= DRAW_WIDTH; i++) {
		t = tmin + (double) i / DRAW_WIDTH * (tmax - tmin);
		sample(t);
	}
}

void
draw_pass2(void)
{
	int i, j, m, n;
	double dx, dy, t, t1, t2, x1, x2, y1, y2;

	n = draw_count;

	for (i = 0; i < n - 1; i++) {

		t1 = draw_buf[i].t;
		t2 = draw_buf[i + 1].t;

		x1 = draw_buf[i].x;
		x2 = draw_buf[i + 1].x;

		y1 = draw_buf[i].y;
		y2 = draw_buf[i + 1].y;

		if (invisible(x1, y1) && invisible(x2, y2))
			continue;

		dx = x2 - x1;
		dy = y2 - y1;

		m = sqrt(dx * dx + dy * dy);

		for (j = 1; j < m; j++) {
			t = t1 + (double) j / m * (t2 - t1);
			sample(t);
		}
	}
}

void
sample(double t)
{
	double x, y;

	if (draw_count == DRAW_MAX)
		return;

	sample_nib(t);

	if (!isnum(XT) || !isnum(YT))
		return;

	push(XT);
	x = pop_double();

	push(YT);
	y = pop_double();

	x = DRAW_WIDTH * (x - xmin) / (xmax - xmin);
	y = DRAW_HEIGHT * (y - ymin) / (ymax - ymin);

	draw_buf[draw_count].x = x;
	draw_buf[draw_count].y = y;
	draw_buf[draw_count].t = t;

	draw_count++;
}

// evaluate F(t) and return in XT and YT

void
sample_nib(double t)
{
	eval_func_arg(t);

	p1 = pop();

	if (istensor(p1)) {
		if (p1->u.tensor->nelem >= 2) {
			XT = p1->u.tensor->elem[0];
			YT = p1->u.tensor->elem[1];
		} else {
			XT = symbol(NIL);
			YT = symbol(NIL);
		}
		return;
	}

	push_double(t);
	XT = pop();
	YT = p1;
}

// evaluate F(t) without stopping due to an error such as divide by zero

void
eval_func_arg(double t)
{
	// These must be volatile or it crashes. (Compiler error?)
	// Read it backwards, save_tos is a volatile int, etc.

	int volatile save_tos;
	int volatile save_tof;

	save();

	save_tos = tos;
	save_tof = tof;

	if (setjmp(draw_stop_return)) {
		tos = save_tos;
		tof = save_tof;
		expanding = 1; // in case stop() occurred in the middle of expanding == 0
		push_symbol(NIL); // return value
		drawing = 1;
		restore(); // restore F, T, etc.
		return;
	}

	push_double(t);
	p1 = pop();
	set_binding(T, p1);

	drawing = 2; // causes stop() to jump to draw_stop_return

	push(F);
	eval();
	sfloat();

	drawing = 1;

	restore();
}

int
invisible(double x, double y)
{
	return x < 0 || x > DRAW_WIDTH || y < 0 || y > DRAW_HEIGHT;
}

void
setup_trange(void)
{
	save();
	setup_trange_nib();
	restore();
}

void
setup_trange_nib(void)
{
	// default range is (-pi, pi)

	tmin = -M_PI;
	tmax = M_PI;

	p1 = get_binding(lookup("trange"));

	// must be two element vector

	if (!istensor(p1) || p1->u.tensor->ndim != 1 || p1->u.tensor->nelem != 2)
		return;

	push(p1->u.tensor->elem[0]);
	eval();
	sfloat();
	p2 = pop();

	push(p1->u.tensor->elem[1]);
	eval();
	sfloat();
	p3 = pop();

	if (!isnum(p2) || !isnum(p3))
		return;

	push(p2);
	tmin = pop_double();

	push(p3);
	tmax = pop_double();

	if (tmin == tmax)
		stop("draw: trange is zero");
}

void
setup_xrange(void)
{
	save();
	setup_xrange_nib();
	restore();
}

void
setup_xrange_nib(void)
{
	// default range is (-10,10)

	xmin = -10.0;
	xmax = 10.0;

	p1 = get_binding(lookup("xrange"));

	// must be two element vector

	if (!istensor(p1) || p1->u.tensor->ndim != 1 || p1->u.tensor->nelem != 2)
		return;

	push(p1->u.tensor->elem[0]);
	eval();
	sfloat();
	p2 = pop();

	push(p1->u.tensor->elem[1]);
	eval();
	sfloat();
	p3 = pop();

	if (!isnum(p2) || !isnum(p3))
		return;

	push(p2);
	xmin = pop_double();

	push(p3);
	xmax = pop_double();

	if (xmin == xmax)
		stop("draw: xrange is zero");
}

void
setup_yrange(void)
{
	save();
	setup_yrange_nib();
	restore();
}

void
setup_yrange_nib(void)
{
	// default range is (-10,10)

	ymin = -10.0;
	ymax = 10.0;

	p1 = get_binding(lookup("yrange"));

	// must be two element vector

	if (!istensor(p1) || p1->u.tensor->ndim != 1 || p1->u.tensor->nelem != 2)
		return;

	push(p1->u.tensor->elem[0]);
	eval();
	sfloat();
	p2 = pop();

	push(p1->u.tensor->elem[1]);
	eval();
	sfloat();
	p3 = pop();

	if (!isnum(p2) || !isnum(p3))
		return;

	push(p2);
	ymin = pop_double();

	push(p3);
	ymax = pop_double();

	if (ymin == ymax)
		stop("draw: yrange is zero");
}
