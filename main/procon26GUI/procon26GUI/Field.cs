using System;
using System.Windows.Forms;
using System.Windows.Input;

namespace Loop
{
    public class Field
    {
        protected Field(int w, int h, int[,] screen, Block[] blocks, int n,bool np)
        {
            W = w; H = h;
            Blocks = blocks;
            Screen = screen;
            N = n;
            NoPutting = np;
            Init();
        }

        public readonly int N;
        public bool NoPutting { get; set; }
        public bool IsPassed{get; set; }
        public readonly int W;
        public readonly int H;
        public int[,] Log = new int[50, 50];
        public int[,] Screen;
        //0...empty, 2...block, 1...obstacle
        public Block[] Blocks { get;set; }
        public Block NowB = new Block();
        public int ScBlock { get; set; }
        public int ScZk{get; set; }
        public int NextScZk { get; set; }
        public int X { get;set; }
        public int Y { get; set; }
        public int Way { get; set; }
        public int Frip { get; set; }
        public int B { get; set; }
        public int WrongIdx { get; set; }
        public bool CanPut { get; set; }
        public bool IsPut { get; set; }
        public bool ConnectFlg { get; set; }

        protected void Init()
        {
            for (int i = 0; i < 32; i++)
            {
                for (int j = 0; j < 32; j++)
                {
                    Log[i, j] = -1;
                }
            }
            NowB = Blocks[0].Clone();
        }
        public virtual void Update(Viewer VW)
        {
            ScZk = 0;
            for (int i = 0; i < H; i++)
            {
                for (int j = 0; j < W; j++)
                {
                    if (Screen[i, j] == 0) ScZk++;
                }
            }
            bool canPut = true;
            ConnectFlg = false;
            if (B != N)
            {
                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        if (i + Y < 0 || H <= i + Y || j + X < 0 || W <= j + X)
                        {
                            if (NowB.D[i, j] == 2) canPut = false;
                            continue;
                        }
                        if (NowB.D[i, j] == 2 && Screen[i + Y, j + X] != 0) canPut = false;
                    }
                }

                CanPut = canPut;
                int[] dx = { 0, 1, 0, -1 };
                int[] dy = { 1, 0, -1, 0 };
                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        for (int k = 0; k < 4; k++)
                        {
                            int nx = X + dx[k];
                            int ny = Y + dy[k];
                            if (j + nx < 0 || W <= j + nx || i + ny < 0 || H <= i + ny) continue;
                            if (NowB.D[i, j] == 2 && Screen[i + ny, j + nx] == 2) ConnectFlg = true;
                        }
                    }
                }
            }
            IsPut = false;
            for (int i = 0; i < 32; i++)
            {
                for (int j = 0; j < 32; j++)
                {
                    if (Screen[i, j] == 2) IsPut = true;

                }
            }
        }
        public void DrawField(Viewer VW)
        {
            VW.Clear();
            int m = Math.Max(W, H);
            VW.Siz = 400 / m;
            VW.DrawNum(330, 0, 30, ScZk, 4, 3);
            VW.DrawNum(400, 0, 30, NextScZk, 4, 3);
            VW.DrawString(470, 30, "zk");
            VW.DrawNum(570, 0, 30, ScBlock, 3, 2);
            VW.DrawString(640, 30, "stones");
            for (int i = 0; i < H; i++)
            {
                for (int j = 0; j < W; j++)
                {
                    VW.DrawPanel(j, i, Screen[i, j]);
                }
            }
            int qx = 0, qxCnt = 0;
            for (int q = B + 1; q < Math.Min(B + 15, N); q++)
            {
                if (qxCnt == 5) { qx++; qxCnt = 0; }
                qxCnt++;
                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        VW.DrawBlock(j, i, qx, (q - B - 1) % 5, Blocks[q].D[i, j]);
                    }
                }
                if (q == WrongIdx)
                {
                    VW.DrawString(500 - 10 + qx * VW.Siz, VW.Top + 20 +((q - B - 1) % 5) * 100,"!",3);
                }
            }

            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    VW.DrawBlock(j, i, -2, 5, NowB.D[i,j]);
                }
            }

            if (B != N && !IsPassed)
            {
                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        if (NowB.D[i, j] == 2)
                            VW.DrawPanel(j + X, i + Y, 3);
                    }
                }


                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        if (i + Y < 0 || H <= i + Y || j + X < 0 || W <= j + X) continue;
                        if (NowB.D[i, j] == 2 && Screen[i + Y, j + X] != 0)
                            VW.DrawChip(j + X, i + Y, Screen[i + Y, j + X]);
                    }
                }
            }
            VW.DrawString(150,30, B == N ? "END" : "b = " + B);
            VW.DrawString(150, 0, "W = " + W + ", H = " + H + ", N = " + N);
            if (IsPassed) VW.DrawString(50, 500, "PASS", 3);
            else  VW.DrawString(50, 500, X + " " + Y + " " + (Frip == 1 ? "T " : "H ") + Way);

        }
    }
}
