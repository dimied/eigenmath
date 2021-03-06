function
arccos()
{
	var p1;

	p1 = pop();

	if (isdouble(p1)) {
		push_double(Math.acos(p1.d));
		return;
	}

	// arccos(z) = -i log(z + sqrt(z^2 - 1))

	if (isdoublez(p1)) {
		push(imaginaryunit);
		negate();
		push(p1);
		push(p1);
		push(p1);
		multiply();
		push_double(-1.0);
		add();
		push_rational(1, 2);
		power();
		add();
		log();
		multiply();
		return;
	}

	// if p1 == 1/sqrt(2) then return 1/4*pi (45 degrees)

	if (isoneoversqrttwo(p1)) {
		push_rational(1, 4);
		push_symbol(PI);
		multiply();
		return;
	}

	// if p1 == -1/sqrt(2) then return 3/4*pi (135 degrees)

	if (isminusoneoversqrttwo(p1)) {
		push_rational(3, 4);
		push_symbol(PI);
		multiply();
		return;
	}

	// arccos(0) = 1/2 pi

	if (iszero(p1)) {
		push_rational(1, 2);
		push_symbol(PI);
		multiply();
		return;
	}

	// arccos(1/2) = 1/3 pi

	if (equalq(p1, 1 ,2)) {
		push_rational(1, 3);
		push_symbol(PI);
		multiply();
		return;
	}

	// arccos(1) = 0

	if (equaln(p1, 1)) {
		push_integer(0);
		return;
	}

	// arccos(-1/2) = 2/3 pi

	if (equalq(p1, -1, 2)) {
		push_rational(2, 3);
		push_symbol(PI);
		multiply();
		return;
	}

	// arccos(-1) = pi

	if (equaln(p1, -1)) {
		push_symbol(PI);
		return;
	}

	push_symbol(ARCCOS);
	push(p1);
	list(2);
}
