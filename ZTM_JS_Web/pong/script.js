// [ object ]
const { body } = document;
const canvas = document.createElement('canvas');
const context = canvas.getContext('2d');

// [ variable ]
// canvas
const width = 500;
const height = 700;
// paddle
const paddleHeight = 10;
const paddleWidth = 50;
const paddleDiffX = paddleWidth / 2;
let paddlePlayerX = width / 2 - paddleDiffX;
let paddleComputerX = width / 2 - paddleDiffX;
const paddleDiffY = 10;
const paddlePlayerY = height - paddleHeight - paddleDiffY;
const paddleComputerY = paddleDiffY;
// ball
const ballRadius = 5;
let ballX = width / 2;
let ballY = height / 2;
// score
const scoreX = 20;
const scorePlayerY = height / 2 + 50;
const scoreComputerY = height / 2 - 30;
const winningScore = 7;
let playerScore = 0;
let computerScore = 0;

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
  renderCanvas();
}

// -------------------------------------------------------------------------- //

createCanvas();