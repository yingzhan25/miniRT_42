// 2. Sub-problem (Pixel colors)
// Requirement: to represent colors

typedef	struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

static int	clamp(int min, int max, int value)
{
	if (value < min)
		return (min);
	else if (value > max)
		return (max);
	return (value);
}

t_color	add_color(t_color x, t_color y)
{
	t_color	ret;

	ret.r = clamp(0, 255, x.r + y.r);
	ret.g = clamp(0, 255, x.g + y.g);
	ret.b = clamp(0, 255, x.b + y.b);
	return (ret);
}

t_color	scale_color(t_color x, float scale)
{
	t_color	ret;

	ret.r = clamp(0, 255, (int)(x.r * scale));
	ret.g = clamp(0, 255, (int)(x.g * scale));
	ret.b = clamp(0, 255, (int)(x.b * scale));
	return (ret);
}