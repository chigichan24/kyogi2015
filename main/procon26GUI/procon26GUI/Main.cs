using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace Loop
{
    class Main
    {
        public Viewer VW;
        readonly string probName;
        readonly int mode;
        Field F;
        readonly string filename;
        readonly bool np;

        public Main(string probName, int mode, string filename, bool np)
        {
            this.probName = probName;
            this.mode = mode;
            this.filename = filename;
            this.np = np;
        }

        public void Init()
        {
            VW = new Viewer(probName);
            VW.Show();
            ReadProb();
            Update();
        }
        public void Update()
        {
            VW.Update();
            F.Update(VW);
            Draw();
        }

        public void Draw()
        {
            string s = probName;
            string[] sp = s.Split('\\');
            F.DrawField(VW);
        }

        public void ReadProb()
        {
            string text;

            using (StreamReader sr = new StreamReader(
                probName, Encoding.GetEncoding("Shift_JIS")))
            {
                text = sr.ReadToEnd();
            }
            text = text.Replace("\r", "\n").Replace("\n\n", "\n");
            var spl = text.Split(' ', '\n', '\r', '\0');

            List<string> sp = new List<string>();
            for (int i = 0; i < spl.Count(); i++)
            {
                if (spl[i] != "")
                    sp.Add(spl[i]);
            }
            var t = 0;
            var screen = new int[50, 50];
            var blocks = new Block[300];
            int N;
            for (int i = 0; i < 32; i++)
            {
                var s = sp[t++];
                for (int j = 0; j < 32; j++)
                {
                    screen[i, j] = s[j] == '1' ? 1 : 0;
                }
            }
            N = int.Parse(sp[t++]);
            for (var q = 0; q < N; q++)
            {
                blocks[q] = new Block();
                for (int i = 0; i < 8; i++)
                {
                    var s = sp[t++];
                    for (int j = 0; j < 8; j++)
                    {
                        blocks[q].D[i, j] = s[j] == '1' ? 2 : 0;
                    }
                }
            }
            switch (mode)
            {
                case 2:
                {
                    var S = new Solver(screen, blocks, N, filename);
                    S.Solve();
                    var wrongIdx = N;
                    if (!np)
                    {
                        wrongIdx = new AutoField(GetW(screen), GetH(screen), screen, blocks, N, S.GetAnswer(), false).TestAnswer();
                    }
                    F = new AutoField(GetW(screen), GetH(screen), screen, blocks, N, S.GetAnswer(), wrongIdx, np);
                }
                    break;
                case 3:
                {
                    var S = new Solver(screen, blocks, N, filename);
                    S.Read();
                    var wrongIdx = N;
                    if (!np)
                    {
                        wrongIdx = new AutoField(GetW(screen), GetH(screen), screen, blocks, N, S.GetAnswer(), false).TestAnswer();
                    }
                    F = new AutoField(GetW(screen), GetH(screen), screen, blocks, N, S.GetAnswer(), wrongIdx, np);
                }
                    break;
                default:
                    F = new ManualField(GetW(screen), GetH(screen), screen, blocks, N);
                    break;
            }
        }

        int GetW(int[,] screen)
        {
            var W = 32;
            for (int i = W - 1; i >= 0; i--)
            {
                var flg = true;
                for (int j = 0; j < 32; j++)
                {
                    if (screen[j, i] == 0) flg = false;
                }
                if (flg && i != 0) continue;
                W = i + 1;
                break;
            }
            return W;
        }
        int GetH(int[,] screen)
        {
            var H = 32;
            for (int i = H - 1; i >= 0; i--)
            {
                bool flg = true;
                for (int j = 0; j < 32; j++)
                {
                    if (screen[i, j] == 0) flg = false;
                }
                if (!flg || i == 0)
                {
                    H = i + 1;
                    break;
                }
            }
            return H;
        }
    }
}
