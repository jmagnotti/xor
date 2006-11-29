

recursivePyramid(origin, base, counter)
{
    if(count < 10)
    {
        ++counter;

        //draw the pyramid at hand
        drawPyramid(origin, base)

        base /= 2;  //we must half the length of the base to determine the position of the next pyramids

        //draw the first pyramid
        Point3D originWorking = new Point3D(origin.getX(), origin.getY(), origin.getZ() + base);
        recursivePyramid(originWorking, base, counter);

        //second pyramid
        delete originWorking;
        originWorking = new Point3D(origin.getX() - base, origin.getY(), origin.getZ() - base);

        recursivePyramid(originWorking, base, counter);

        //third pyramid
        delete originWorking;
        originWorking = new Point3D(origin.getX() + base, origin.getY(), origin.getZ() - base);

        recursivePyramid(originWorking, base, counter);

        //fourth pyramid
        delete originWorking;
        originWorking = new Point3D(origin.getX(), origin.getY() + base, origin.getZ());

        recursivePyramid(originWorking, base, counter);
    }
}



