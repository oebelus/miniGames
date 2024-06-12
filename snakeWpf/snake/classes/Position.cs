using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace snake.classes
{
    internal class Position(int row, int column)
    {
        public int Row { get; } = row;
        public int Column { get; } = column;

        public Position Translate(Direction dir)
        {
            return new Position(Row + dir.RowOffset, Column + dir.ColumnOffset);
        }

        public static Position RandomPosition(int rows, int cols)
        {
            Random random = new();

            int randomRow = random.Next(0, rows);
            int randomColumn = random.Next(0, cols);

            return new Position(randomRow, randomColumn);
        }
    }
}
