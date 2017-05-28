using System;
using System.Windows.Forms;
using System.Windows.Input;

namespace Loop
{
    public class AutoField : Field
    {
        public AutoField(int W, int H, int[,] screen, Block[] blocks, int N, Answer[] ans, int wrongIdx, bool np)
            : base(W, H, screen, blocks, N, np)
        {
            this.ans = ans;
            WrongIdx = wrongIdx;
            ReadAnswer(0);
        }
        public AutoField(int W, int H, int[,] screen, Block[] blocks, int N, Answer[] ans, bool np)
            : base(W, H, screen, blocks, N, np)
        {
            this.ans = ans;
            ReadAnswer(0);
        }

        readonly Answer[] ans;
        public void ReadAnswer(int t)
        {
            IsPassed = ans[t].isPassed;
            if (ans[t].isPassed || t == N)
            {
                IsPassed = true;
                Y = H;
                X = 0;
                if (t != N)
                {
                    Block B = Blocks[t].Clone();
                    NowB = B;
                }
            }
            else
            {

                Block B = Blocks[t].Clone();
                X = ans[t].x;
                Y = ans[t].y;
                Way = ans[t].way;
                if (Way % 90 == 0) Way /= 90;
                Frip = ans[t].frip;
                if (Frip == 1) B.Frip();
                B.Rotate(Way);

                NowB = B;
            }
        }
        public override void Update(Viewer VW)
        {
            base.Update(VW);
            int th = 20;
            if (VW.GetIsKeyPressed(Key.Left) || VW.GetTimeKeyPressing(Key.Left) > th)
            {
                if (B != 0)
                {
                    B--;
                    ReadAnswer(B);
                    for (int i = 0; i < 32; i++)
                    {
                        for (int j = 0; j < 32; j++)
                        {
                            if (Log[i, j] == B)
                            {
                                Log[i, j] = -1;
                                Screen[i, j] = 0;
                            }
                        }
                    }
                }

            }
            if (VW.GetIsKeyPressed(Key.Right) || VW.GetTimeKeyPressing(Key.Right) > th)
            {
                if (B != N && B != WrongIdx)
                {
                    if (!IsPassed & !NoPutting)
                    {
                        for (int i = 0; i < 8; i++)
                        {
                            for (int j = 0; j < 8; j++)
                            {
                                if (NowB.D[i, j] == 2)
                                {
                                    Screen[i + Y, j + X] = 2;
                                    Log[i + Y, j + X] = B;
                                }
                            }
                        }
                    }
                    B++;
                    if (B != N)
                        ReadAnswer(B);
                }
            }
        }

        public int TestAnswer()
        {
            int[,] sc = new int[50, 50];
            for (int i = 0; i < 32; i++)
            {
                for (int j = 0; j < 32; j++)
                {
                    sc[i, j] = Screen[i, j];
                }
            }
            for (int q = 0; q < N; q++)
            {
                Console.WriteLine(@"{0},{1},{2},{3},{4}", X, Y, Frip, Way, IsPassed);
                bool canPut = true;
                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        if (i + Y < 0 || H <= i + Y || j + X < 0 || W <= j + X)
                        {
                            if (NowB.D[i, j] == 2)
                            {
                                canPut = false;
                            }
                            continue;
                        }
                        if (NowB.D[i, j] == 2 && sc[i + Y, j + X] != 0)
                        {
                            canPut = false;
                        }
                    }
                }

                CanPut = canPut;
                int[] dx = { 0, 1, 0, -1 };
                int[] dy = { 1, 0, -1, 0 };
                ConnectFlg = false;
                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        for (int k = 0; k < 4; k++)
                        {
                            int nx = X + dx[k];
                            int ny = Y + dy[k];
                            if (j + nx < 0 || W <= j + nx || i + ny < 0 || H <= i + ny) continue;
                            if (NowB.D[i, j] == 2 && sc[i + ny, j + nx] == 2) ConnectFlg = true;
                        }
                    }
                }
                IsPut = false;
                for (int i = 0; i < 32; i++)
                {
                    for (int j = 0; j < 32; j++)
                    {
                        //Console.Write(@"{0}", sc[i, j]);
                        if (sc[i, j] == 2) IsPut = true;
                    }
                    //Console.WriteLine();
                }
                if (!IsPassed)
                {
                    if (!CanPut || (IsPut && !ConnectFlg)) return q;
                    for (int i = 0; i < 8; i++)
                    {
                        for (int j = 0; j < 8; j++)
                        {
                            if (NowB.D[i, j] == 2)
                            {
                                sc[i + Y, j + X] = 2;
                            }
                        }
                    }
                }
                ReadAnswer(q+1);
            }
            return N;
        }
    }
}
