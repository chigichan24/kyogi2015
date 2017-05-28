using System.Windows.Forms;
using System.Windows.Input;

namespace Loop
{
    public class ManualField : Field
    {
        public ManualField(int W, int H, int[,] _screen, Block[] _blocks, int n)
        :base(W,H, _screen, _blocks, n,false){}
       
        public override void Update(Viewer VW)
        {
            base.Update(VW);
            int th = 20;
            if (VW.GetIsKeyPressed(Key.Left) || VW.GetTimeKeyPressing(Key.Left) > th) X--;
            if (VW.GetIsKeyPressed(Key.Right) || VW.GetTimeKeyPressing(Key.Right) > th) X++;
            if (VW.GetIsKeyPressed(Key.Up) || VW.GetTimeKeyPressing(Key.Up) > th) Y--;
            if (VW.GetIsKeyPressed(Key.Down) || VW.GetTimeKeyPressing(Key.Down) > th) Y++;
            if (VW.GetIsKeyPressed(Key.Z) && B != N)
            {
                NowB.Rotate(3);
                Way = (Way + 3) % 4;
            }
            if (VW.GetIsKeyPressed(Key.X) && B != N)
            {
                NowB.Rotate(1);
                Way = (Way + 1) % 4;
            }
            if (VW.GetIsKeyPressed(Key.C) && B != N)
            {
                NowB.Frip();
                Frip = 1 - Frip;
                Way = (4 - Way)%4;
            }
            if (VW.GetIsKeyPressed(Key.Space) && B != N)
            {
                NowB.Rotate(4 - Way);
                if (Frip == 1) NowB.Frip();
                Way = 0; Frip = 0;

                B++;

                if(B!=N)NowB = Blocks[B].Clone();

            }
            if (VW.GetIsKeyPressed(Key.Enter) && B != N)
            {
                
                if ((!IsPut || ConnectFlg) && CanPut)
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
                    
                    NowB.Rotate(4 - Way);
                    if (Frip == 1) NowB.Frip();
                    Way = 0; Frip = 0;
                    
                    
                    B++;
                    if(B != N)NowB = Blocks[B].Clone();
                    ScBlock++;
                }
            }
            if (VW.GetIsKeyPressed(Key.Back) && B != 0)
            {
                B--;
                NowB = Blocks[B].Clone();

                Way = 0; Frip = 0;
                
                bool flg = false;
                for (int i = 0; i < 32; i++)
                {
                    for (int j = 0; j < 32; j++)
                    {
                        if (Log[i, j] == B)
                        {
                            flg = true;
                            Log[i, j] = -1;
                            Screen[i, j] = 0;
                        }
                    }
                }
                if(flg)ScBlock--;
            }
        }
    }
}
