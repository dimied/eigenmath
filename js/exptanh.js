function
exptanh()
{
	var p1;
	push_integer(2);
	multiply();
	exp();
	p1 = pop();
	push(p1);
	push_integer(1);
	subtract();
	push(p1);
	push_integer(1);
	add();
	divide();
}
