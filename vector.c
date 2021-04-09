typedef struct  s_vec
{
    double x;
    double y;
}               t_vec;

t_vec   new_vector(double x, double y)
{
    t_vec   ret;

    ret.x = x;
    ret.y = y;
    return (ret);
}