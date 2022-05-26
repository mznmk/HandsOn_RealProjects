// [ object ]
const { body } = document;
const canvas = document.createElement('canvas');
const context = canvas.getContext('2d');
const gameOverEl = document.createElement('div');

// -------------------------------------------------------------------------- //

// [ variable ]
// canvas
const width = 500;
const height = 700;
const screenWidth = window.screen.width;
const canvasX = screenWidth / 2 - width / 2;
// ball
const ballRadius = 5;
const ballDiameter = ballRadius * 2;
let ballX = width / 2;
let ballY = height / 2;
// paddle
const paddleHeight = 10;
const paddleWidth = 80;
let paddlePlayerX = width / 2 - paddleWidth / 2;
let paddleComputerX = width / 2 - paddleWidth / 2;
const paddlePlayerY = height - ballDiameter - paddleHeight;
const paddleComputerY = ballDiameter;
let playerMoved = false;
/// speed
const baseSpeed = 5;
const maxSpeed = 15;
const computerSpeed = baseSpeed;
let speedX;
let speedY;
let trajectoryX;
// score
const scoreX = 20;
const scorePlayerY = height / 2 + 50;
const scoreComputerY = height / 2 - 30;
const winningScore = 3;
let playerScore = 0;
let computerScore = 0;
let isGameOver = true;
let isNewGame = true;

// -------------------------------------------------------------------------- //

// [ render canvas ]
function renderCanvas() {
  // canvas background
  context.fillStyle = 'black';
  context.fillRect(0, 0, width, height);
  // paddle
  context.fillStyle = 'white';
  context.fillRect(paddlePlayerX, paddlePlayerY, paddleWidth, paddleHeight);
  context.fillRect(paddleComputerX, paddleComputerY, paddleWidth, paddleHeight);
  // center line
  context.beginPath();
  context.setLineDash([4]);
  context.moveTo(0, height / 2);
  context.lineTo(width, height / 2);
  context.strokeStyle = 'gray';
  context.stroke();
  // ball 
  context.beginPath();
  context.arc(ballX, ballY, ballRadius, 0, Math.PI * 2, false);
  context.fillStyle = 'white';
  context.fill();
  // score
  context.font = '32px Courier New';
  context.fillText(playerScore, scoreX, scorePlayerY);
  context.fillText(computerScore, scoreX, scoreComputerY);
}

// [ create canvas ]
function createCanvas() {
  canvas.width = width;
  canvas.height = height;
  body.appendChild(canvas);
}

// [ show game over element ]
function showGameOverEl(winner) {
  // hide canvas
  canvas.hidden = true;
  // container
  gameOverEl.textContent = "";
  gameOverEl.classList.add('game-over-container');
  // title
  const title = document.createElement('h1');
  title.textContent = `${winner} Wins!`;
  // button
  const playAgainBtn = document.createElement('button');
  playAgainBtn.setAttribute('onclick', 'startGame()');
  playAgainBtn.textContent = 'Play Again';
  // append
  gameOverEl.append(title, playAgainBtn);
  body.appendChild(gameOverEl);
}

// -------------------------------------------------------------------------- //

// [ reset ball ]
function resetBall() {
  speedY = baseSpeed;
  speedX = 0;
  ballX = width / 2;
  ballY = height / 2;
}

// [ move ball position ]
function ballMove() {
  ballY += speedY;
  ballX += speedX;
}

// [ ball reach each boundary ]
function ballBoundaries() {
  // reach left boundary (left wall)
  if (ballX < ballRadius && speedX < 0) {
    speedX *= -1;
  }
  // reach right boundary (right wall)
  if (width - ballRadius < ballX && 0 < speedX) {
    speedX *= -1;
  }
  // reach bottom boundary (player paddle)
  if (paddlePlayerY - ballRadius < ballY) {
    if (paddlePlayerX - ballRadius < ballX &&
      ballX < paddlePlayerX + paddleWidth + ballRadius) {
        // set ballY
        ballY = paddlePlayerY - ballRadius;
        // set speedY
        speedY++;
        if (maxSpeed < speedY) { speedY = maxSpeed; }
        speedY *= -1;
        // set speedX
        trajectoryX = ballX - (paddlePlayerX + paddleWidth / 2);
        speedX = trajectoryX / ballRadius;
      } else if (height - ballRadius < ballY) {
        resetBall();
        computerScore++;
      }
    }
    // reach top boundary (computer paddle)
    if (ballY < paddleComputerY + paddleHeight + ballRadius) {
      // hit paddle ?
      if (paddleComputerX - ballRadius < ballX &&
        ballX < paddleComputerX + paddleWidth + ballRadius) {
          // set ballY
          ballY = paddleComputerY + paddleHeight + ballRadius;
          // set speedY
          speedY--;
          if (speedY < -maxSpeed) { speedY = -maxSpeed; }
          speedY *= -1;
          // set speedX
          trajectoryX = ballX - (paddleComputerX + paddleWidth / 2);
          speedX = trajectoryX / ballRadius;   
        } else if (ballY < ballRadius) {
          resetBall();
          playerScore++;
        }
  }
}

// [ move computer ]
function moveComputer() {
  if (playerMoved) {
    // trace ballX
    if (paddleComputerX + paddleWidth / 2 < ballX) {
      // move right
      paddleComputerX += computerSpeed;
      if (width - paddleWidth < paddleComputerX) {
        paddleComputerX = width - paddleWidth;
      }
    } else {
      // move left
      paddleComputerX -= computerSpeed;
      if (paddleComputerX < 0) {
        paddleComputerX = 0;
      } 
    }
  }
}

// -------------------------------------------------------------------------- //

// [ game over ]
function gameOver() {
  // player win ?
  if (playerScore === winningScore) {
    isGameOver = true;
    showGameOverEl("Player");
  }
  // computer win ?
  if (computerScore === winningScore) {
    isGameOver = true;
    showGameOverEl("Computer");
  }
}

// [ animate ]
function animate() {
  renderCanvas();
  ballMove();
  ballBoundaries();
  moveComputer();
  gameOver();
  if (!isGameOver) {
    window.requestAnimationFrame(animate);
  }
}

// [ start game ]
function startGame() {
  // game over -> restart game
  if (isGameOver && !isNewGame) {
    body.removeChild(gameOverEl);
    canvas.hidden = false;
  }
  // set status
  isGameOver = false;
  isNewGame = false;
  // reset parameter
  playerScore = 0;
  computerScore = 0;
  resetBall();
  // start game
  createCanvas();
  animate();
   // add event (move player)
  canvas.addEventListener('mousemove', (e) => {
    playerMoved = true;
    // calc paddle position
    paddlePlayerX = e.clientX - canvasX - paddleWidth / 2;
    if (paddlePlayerX < 0) {
      paddlePlayerX = 0;
    }
    if (width - paddleWidth < paddlePlayerX) {
      paddlePlayerX = width - paddleWidth;
    }
    // hide cursor
    canvas.style.cursor = 'none';
  });
}

// -------------------------------------------------------------------------- //

// [ on load ]
startGame();