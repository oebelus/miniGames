using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Shapes;

namespace snake.classes
{
    internal class Apple
    {
        private readonly Ellipse ellipse;
        private readonly int Width;
        public Position Position;

        public Apple(int width, Position position)
        {
            Width = width;
            Position = position;

            ellipse = new()
            {
                Width = width,
                Height = width,
                Fill = Brushes.Red
            };
        }

        public void Draw(Canvas canvas)
        {
            Canvas.SetLeft(ellipse, Position.Column * Width);
            Canvas.SetTop(ellipse, Position.Row * Width);
            canvas.Children.Add(ellipse);
        }

        public void ClearApple(Canvas canvas)
        {
            canvas.Children.Remove(ellipse);
        }
    }
}
