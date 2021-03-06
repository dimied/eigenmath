function
power_sum(BASE, EXPO)
{
	var h, i, n, p3, p4;

	if (expanding == 0 || !isnum(EXPO)) {
		push_symbol(POWER);
		push(BASE);
		push(EXPO);
		list(3);
		return;
	}

	if (isrational(EXPO))
		n = EXPO.a / EXPO.b;
	else
		n = EXPO.d;

	if (n < 0 || n != Math.floor(n)) {
		push_symbol(POWER);
		push(BASE);
		push(EXPO);
		list(3);
		return;
	}

	// square the sum first (prevents infinite loop through multiply)

	h = stack.length;

	p3 = cdr(BASE);

	while (iscons(p3)) {
		p4 = cdr(BASE);
		while (iscons(p4)) {
			push(car(p3));
			push(car(p4));
			multiply();
			p4 = cdr(p4);
		}
		p3 = cdr(p3);
	}

	add_terms(stack.length - h);

	// continue up to power n

	for (i = 2; i < n; i++) {
		push(BASE);
		multiply();
	}
}
