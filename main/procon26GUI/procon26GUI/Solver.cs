using System.Diagnostics;
using System.IO;
using System.Text;

namespace Loop
{
    public class Solver
    {
        readonly int[,] screen;
        readonly Block[] blocks;
        readonly int N;
        readonly Answer[] ans = new Answer[1050];
        readonly string filename;
        public string debugLog = "";
        public Solver(int[,] screen, Block[] blocks, int N, string filename)
        {
            this.screen = screen;
            this.blocks = blocks;
            this.N = N;
            this.filename = filename;
            for (var q = 0; q <= N; q++)
            {
                ans[q] = new Answer();
            }
        }

        public void Read()
        {
            string output;

            using (var sr = new StreamReader(
                filename, Encoding.GetEncoding("Shift_JIS")))
            {
                output = sr.ReadToEnd();
            }

            output = output.Replace("\r", "\n").Replace("\n\n", "\n");
            var spl = output.Split('\n');
            var t = 0;
            for (var i = 0; i < N; i++)
            {
                var s = spl[t++].Split(' ');
                if (s[0] == "") ans[i].isPassed = true;
                else if (s[0][0] == '#')
                {
                    i--;
                }
                else
                {
                    ans[i].x = int.Parse(s[0]);
                    ans[i].y = int.Parse(s[1]);
                    ans[i].frip = s[2] == "T" ? 1 : 0;
                    ans[i].way = int.Parse(s[3]);
                }
            }
        }
        public void Solve()
        {
            var psInfo = new ProcessStartInfo
            {
                FileName = filename,
                CreateNoWindow = false,
                RedirectStandardInput = true,
                RedirectStandardOutput = true,
                UseShellExecute = false
            };
            var p = Process.Start(psInfo);
            if (p != null)
            {
                for (var i = 0; i < 32; i++)
                {
                    for (var j = 0; j < 32; j++)
                    {
                        p.StandardInput.Write(screen[i, j] == 0 ? 0 : 1);
                    }

                    p.StandardInput.WriteLine();
                }
                p.StandardInput.WriteLine(N);
                for (var q = 0; q < N; q++)
                {
                    p.StandardInput.WriteLine();
                    for (var i = 0; i < 8; i++)
                    {
                        for (var j = 0; j < 8; j++)
                        {
                            p.StandardInput.Write(blocks[q].D[i, j]);
                        }
                        p.StandardInput.WriteLine();
                    }
                }
                var output = p.StandardOutput.ReadToEnd();
                output = output.Replace("\r", "\n").Replace("\n\n", "\n");
                var spl = output.Split('\n');
                var t = 0;
                for (var i = 0; i < N; i++)
                {
                    var s = spl[t++].Split(' ');
                    if (s[0] == "") ans[i].isPassed = true;
                    else if (s[0][0] == '#')
                    {
                        i--;
                    }
                    else
                    {
                        ans[i].x = int.Parse(s[0]);
                        ans[i].y = int.Parse(s[1]);
                        ans[i].frip = s[2] == "T" ? 1 : 0;
                        ans[i].way = int.Parse(s[3]);
                    }
                }
            }
        }

        public Answer[] GetAnswer()
        {
            return ans;
        }
    }
}
