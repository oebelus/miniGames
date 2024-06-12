namespace snake.classes
{
    internal class Direction
    {
        public readonly static Direction Left = new(0, -1);
        public readonly static Direction Right = new(0, 1);
        public readonly static Direction Up = new(-1, 0);
        public readonly static Direction Down = new(1, 0);

        public int RowOffset { get; }
        public int ColumnOffset { get; }

        private Direction(int rowOffset, int columnOffset)
        {
            this.RowOffset = rowOffset;
            this.ColumnOffset = columnOffset;
        }
    }
}
