using snake.classes;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media.Imaging;
using System.Windows.Threading;

namespace snake
{
    public partial class MainWindow : Window
    {
        private Snake? snake;
        private Apple? apple;

        private int Score = 0;

        private int snakeSize = 1;
        private readonly int snakeWidth = 40;
        private readonly LinkedList<Position> positions = new();

        private readonly snake.classes.Position startPosition = new(3, 2);
        private readonly Direction snakeDirection = Direction.Right;

        private readonly int rows = 12;
        private readonly int cols = 12;

        private int canvasHeight, canvasWidth;

        readonly DispatcherTimer gameTimer = new();

        public MainWindow()
        {
            InitializeComponent();

            CanvasGrid.Focus();

            snekPawsition.Text = "Press any key to start the game";

            this.KeyDown += new KeyEventHandler(OnKeyDown);

            InitializeGame();
        }

        private void OnKeyDown(object sender, KeyEventArgs e)
        {
            if (!gameTimer.IsEnabled)
            {
                snekPawsition.Text = "";
                StartGame();
            }
        }

        public void InitializeGame()
        {
            canvasHeight = (int) CanvasGrid.ActualHeight;
            canvasWidth = (int) CanvasGrid.ActualHeight;

            snake = new Snake(snakeSize, snakeWidth, positions, startPosition, snakeDirection, false, Score);
            snake.Draw(CanvasGrid);

            apple = new Apple(snakeWidth, Position.RandomPosition(rows, cols));
            apple.Draw(CanvasGrid);
        }

        public void StartGame()
        {
            gameTimer.Tick += GameLoop;
            gameTimer.Interval = TimeSpan.FromMilliseconds(100);
            gameTimer.Start();
        }

        private void GameLoop(object sender, EventArgs e)
        {
            if (!snake!.GameOver)
            {
                snake!.Move(CanvasGrid);
                snake.Draw(CanvasGrid);
                
                if (apple!.Position.Row == snake.Position.Row && apple!.Position.Column == snake.Position.Column)
                {   
                    apple.ClearApple(CanvasGrid);

                    var applePos = Position.RandomPosition(rows, cols);
                    foreach (var pos in snake.Positions)
                    {
                        if (applePos.Row == pos.Row && applePos.Column == pos.Column) 
                            applePos = Position.RandomPosition(rows, cols);
                    }

                    apple = new Apple(snakeWidth, applePos);
                    apple.Draw(CanvasGrid);

                    snake.ClearSnake(CanvasGrid);

                    positions.AddLast(snake.Position);
                    snake = new Snake(++snakeSize, snakeWidth, positions, snake.Position, snake.Direction, false, ++Score); 
                    snake.Draw(CanvasGrid);

                    GameScore.Text = snake.Score.ToString();
                }
            }
            else
            {
                CanvasGrid.Children.Clear();
                snekPawsition.Text = "GAME OVER";

                gameTimer.Stop();
            }
        }

        private void Canvas_KeyDown(object sender, System.Windows.Input.KeyEventArgs e)
        {
            if (snake == null || snake.GameOver)
                return;

            switch (e.Key)
            {
                case Key.Left:
                    if ((snake!.Direction != Direction.Right && snake.Size > 1) || snake.Size == 1)
                        snake!.ChangeDirection(Direction.Left);
                    break;
                case Key.Right:
                    if ((snake!.Direction != Direction.Left && snake.Size > 1) || snake.Size == 1)
                        snake!.ChangeDirection(Direction.Right);
                    break;
                case Key.Up:
                    if ((snake!.Direction != Direction.Down && snake.Size > 1) || snake.Size == 1)
                        snake!.ChangeDirection(Direction.Up);
                    break;
                case Key.Down:
                    if ((snake!.Direction != Direction.Up && snake.Size > 1) || snake.Size == 1)
                        snake!.ChangeDirection(Direction.Down);
                    break;
            }
        }
    }
}