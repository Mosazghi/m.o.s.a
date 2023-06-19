const canvas = document.getElementById('topdown');

canvas.addEventListener('click', (e) => {
  const x = e.clientX - canvas.offsetLeft;
  const y = e.clientY - canvas.offsetTop;
  document.getElementById('x').value = x;
  document.getElementById('y').value = y;
  console.log(`(${x}, ${y})`);
});

const form = document.querySelector('form');
form.addEventListener('submit', async (e) => {
  e.preventDefault(); // Hindrer siden i å refreshe når sumbit
  const formData = new FormData(form);

  const data = {
    x: formData.get('x'),
    y: formData.get('y'),
  };

  if (x !== '' && y !== '') {
    await fetch('http://localhost:3000/koordinater', {
      method: 'POST',
      body: JSON.stringify(data),
      headers: {
        'Content-type': 'application/json; charset=UTF-8',
      },
    });

    await displayKoordinat();
  } else console.log('MÅ inneholde begge koordinater!');
});

const div = document.getElementById('display-koordinat');

async function displayKoordinat() {
  const res = await fetch('http://localhost:3000/koordinater', {
    method: 'GET',
  });
  console.log('data: ', res);
  const data = await res.json();
  div.innerHTML = `Du sendte koordinatene x=${data.x}, y=${data.y} til M.O.S.A!`;
}

canvas.addEventListener('mousemove', (e) => {
  const x = e.clientX - canvas.offsetLeft;
  const y = e.clientY - canvas.offsetTop;
  document.getElementById(
    'xyKoordinater',
  ).innerHTML = `Koordinater: (${x}, ${y} )`;
});
canvas.addEventListener('mouseleave', (e) => {
  document.getElementById('xyKoordinater').innerHTML = '';
});

const SIZE = 24;

const tp = document.getElementById('topdown');
tp.style.gridTemplateColumns = `repeat(${SIZE}, 1fr)`;
tp.style.gridTemplateRows = `repeat(${SIZE}, 1fr)`;

for (let k = 0; k < SIZE * SIZE; k++) {
  const element = document.createElement('div');
  element.className = 'grid-element';
  canvas.appendChild(element);
  element.addEventListener('click', (e) => {
    element.style.backgroundColor = 'red';
  });
}

// var scene = document.getElementById('topdown');
// var ctx = scene.getContext('2d');

// scene.width = 600;
// scene.height = 600;
// function drawGrid(startX, startY, endX, endY, gridCellSize) {
//   ctx.beginPath();
//   ctx.lineWidth = 1;

//   for (x = startX; x <= endX; x += gridCellSize) {
//     ctx.moveTo(x, startY);
//     ctx.lineTo(x, endY);
//   }

//   for (y = startY; y <= endY; y += gridCellSize) {
//     ctx.moveTo(startX, y);
//     ctx.lineTo(endX, y);
//   }

//   ctx.strokeStyle = '#ffffff';
//   ctx.stroke();
//   ctx.closePath();
// }

// function main() {
//   ctx.clearRect(0, 0, scene.width, scene.height);
//   ctx.fillStyle = '#000000';
//   ctx.fillRect(0, 0, scene.width, scene.height);

//   drawGrid(0, 0, scene.width, scene.height, 15);
//   ctx.strokeStyle = '#fff';
//   ctx.moveTo(0, 0);
//   ctx.lineTo(200, 100);
//   ctx.stroke();
//   requestAnimationFrame(main);
// }

// window.onload = function () {
//   main();
// };
