namespace Loop
{
    public class Block
    {
        public Block Clone()
        {
            var b = new Block();
            for (int i = 0; i < 10; i++)
            {
                for (int j = 0; j < 10; j++)
                {
                    b.D[i, j] = D[i, j];
                }
            }
            return b;
        }
        public int[,] D = new int[10, 10];

        public void Rotate(int angle)
        {
            var nD = new int[10, 10];

            for (int k = 0; k < angle; k++)
            {
                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        nD[i, j] = D[7 - j, i];
                    }
                }
                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        D[i, j] = nD[i, j];
                    }
                }
            }
        }
        public void Frip()
        {
            var nD = new int[10, 10];

            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    nD[i, j] = D[i, 7 - j];
                }
            }
            D = nD;
        }
    }
}
