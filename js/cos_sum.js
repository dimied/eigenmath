function
cos_sum(p1) // cos(x + n/2 pi) = cos(x) cos(n/2 pi) - sin(x) sin(n/2 pi)
{
	var p2, p3;
	p2 = cdr(p1);
	while (iscons(p2)) {
		push_integer(2);
		push(car(p2));
		multiply();
		push_symbol(PI);
		divide();
		p3 = pop();
		if (isinteger(p3)) {
			push(p1);
			push(car(p2));
			subtract();
			p3 = pop();
			push(p3);
			cos();
			push(car(p2));
			cos();
			multiply();
			push(p3);
			sin();
			push(car(p2));
			sin();
			multiply();
			subtract();
			return;
		}
		p2 = cdr(p2);
	}
	push_symbol(COS);
	push(p1);
	list(2);
}
