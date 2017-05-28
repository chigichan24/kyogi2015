using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Windows.Input;

namespace Loop
{
    internal class InputMaster
    {
        private bool[] isKeyPressed = new bool[20];
        private bool[] isKeyPressing = new bool[20];
        private int[]  timeKeyPressing = new int[20];
        
        public void Update()
        {   
        
            for (int i = 0; i < keyList.Count(); i++)
            {
                if (isKeyPressing[i]) timeKeyPressing[i]++;
                else timeKeyPressing[i] = 0;
                isKeyPressing[i] = false;
            }
            for (int i = 0; i < keyList.Count(); i++)
            {
                if (Keyboard.IsKeyDown(keyList[i]))
                {
                    isKeyPressing[i] = true;
                }
            }
            for (int i = 0; i < keyList.Count(); i++)
            {
                if (isKeyPressing[i] && timeKeyPressing[i] == 0) isKeyPressed[i] = true;
                else isKeyPressed[i] = false;
            }
        }

        public int GetTimeKeyPressing(Key key)
        {
            for (int i = 0; i < keyList.Count(); i++)
            {
                if (key == keyList[i]) return timeKeyPressing[i];
            }
            return 0;
        }
        public bool GetIsKeyPressed(Key key)
        {
            for (int i = 0; i < keyList.Count(); i++)
            {
                if (key == keyList[i]) return isKeyPressed[i];
            }
            return false;
        }
        Key[] keyList = new[] {Key.Up , Key.Down, Key.Left, Key.Right, Key.Enter, Key.Z, Key.X, Key.C, Key.Space,Key.Back };
        
    }
}
