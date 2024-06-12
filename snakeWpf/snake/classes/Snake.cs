using System.Windows.Shapes;
using System.Windows.Media;
using System.Windows.Controls;
using System.Diagnostics;

namespace snake.classes
{
    internal class Snake
    {
        public LinkedList<Rectangle> Body { get; private set; }
        public LinkedList<Position> Positions { get; private set; }
        public int Size;
        private readonly int Width;
        public Position Position;
        public Direction Direction;
        public int Score { get; }
        public bool GameOver { get; set; }

        public Snake(int size, int width, LinkedList<Position> positions,Position position, Direction direction, bool gameOver, int score)
        {
            Body = [];
            Size = size;
            Width = width;
            Positions = positions ?? new LinkedList<Position>(); 
            Position = position;
            Direction = direction;
            GameOver = gameOver;
            Score = score;

            for (int i = 0; i < size; i++)
            {
                Rectangle rect = new()
                {
                    Width = width,
                    Height = width,
                    Fill = i == 0 ? Brushes.Black: Brushes.Green,
                };
                Body.AddLast(rect);
            }

            if (Positions.Count == 0)
            {
                for (int i = 0; i < size; i++)
                {
                    Positions.AddLast(new Position(position.Row, position.Column - i));
                }
            }
        }

        public void ChangeDirection(Direction direction)
        {
            Direction = direction;
        }

        public void Move(Canvas canvas)
        {
            Position newHead = Position.Translate(Direction); 

            if (newHead.Row * Width >= canvas.ActualWidth || newHead.Row < 0 ||
                newHead.Column * Width >= canvas.ActualHeight|| newHead.Column < 0)
            {
                GameOver = true;
            }

            foreach (var pos in Positions)
            {
                if (newHead.Row == pos.Row && newHead.Column == pos.Column) GameOver = true ;
            }

            Positions.AddFirst(newHead);
            Positions.RemoveLast();

            Position = newHead;
        }

        public void Draw(Canvas canvas)
        {
            foreach (var rect in Body)
            {
                canvas.Children.Remove(rect);
            }

            LinkedList<Position>.Enumerator positionEnumerator = Positions.GetEnumerator();
            LinkedList<Rectangle>.Enumerator bodyEnumerator = Body.GetEnumerator();

            Trace.WriteLine(positionEnumerator);

            while (positionEnumerator.MoveNext() && bodyEnumerator.MoveNext())
            {
                var position = positionEnumerator.Current;
                var rect = bodyEnumerator.Current;

                Canvas.SetLeft(rect, position.Column * Width);
                Canvas.SetTop(rect, position.Row * Width);
            }

            foreach (var rectangle in Body) { canvas.Children.Add(rectangle); }
        }

        public void ClearSnake(Canvas canvas)
        {
            for (int i = 0; i < Size; i++)
            {
                canvas.Children.Remove(Body.ElementAt(i));
            }
        }
    }
}
