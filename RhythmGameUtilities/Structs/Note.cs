using System;
using System.Runtime.InteropServices;

namespace RhythmGameUtilities
{

    [StructLayout(LayoutKind.Sequential)]
    public struct Note : IEquatable<Note>
    {

        public int ID;

        public int Position;

        public int HandPosition;

        public int Length;

        public override int GetHashCode()
        {
            return (ID, Position, HandPosition, Length).GetHashCode();
        }

        public bool Equals(Note other)
        {
            return ID == other.ID && Position == other.Position && HandPosition == other.HandPosition && Length == other.Length;
        }

        public override bool Equals(object obj)
        {
            return obj is Note other && Equals(other);
        }

        public static bool operator ==(Note left, Note right)
        {
            return left.Equals(right);
        }

        public static bool operator !=(Note left, Note right)
        {
            return !(left == right);
        }

    }

}
