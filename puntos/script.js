const canvas = document.getElementById("canvas");
const ctx = canvas.getContext("2d");
canvas.width = innerWidth;
canvas.height = innerHeight;

window.onresize = ()=>{
  canvas.width = innerWidth;
  canvas.height = innerHeight;
};

const btn = document.getElementById("btn");
const wordInput = document.getElementById("wordInput");
const phaseBox = document.getElementById("phaseBox");

const CELL = 14;
const RADIUS = 2;
const SPEED = 2;
const ROW_DELAY = 10;

const MATRIX_ROWS = 14;
const LETTER_ROWS = 7;

const LETTERS = {
 A:["01110","10001","10001","11111","10001","10001","10001"],
 B:["11110","10001","10001","11110","10001","10001","11110"],
 C:["01110","10001","10000","10000","10000","10001","01110"],
 D:["11110","10001","10001","10001","10001","10001","11110"],
 E:["11111","10000","10000","11110","10000","10000","11111"],
 F:["11111","10000","10000","11110","10000","10000","10000"],
 G:["01110","10001","10000","10111","10001","10001","01110"],
 H:["10001","10001","10001","11111","10001","10001","10001"],
 I:["11111","00100","00100","00100","00100","00100","11111"],
 J:["11111","00010","00010","00010","00010","10010","01100"],
 K:["10001","10010","10100","11000","10100","10010","10001"],
 L:["10000","10000","10000","10000","10000","10000","11111"],
 M:["10001","11011","10101","10101","10001","10001","10001"],
 N:["10001","11001","10101","10011","10001","10001","10001"],
 O:["01110","10001","10001","10001","10001","10001","01110"],
 P:["11110","10001","10001","11110","10000","10000","10000"],
 Q:["01110","10001","10001","10001","10101","10010","01101"],
 R:["11110","10001","10001","11110","10100","10010","10001"],
 S:["01110","10001","10000","01110","00001","10001","01110"],
 T:["11111","00100","00100","00100","00100","00100","00100"],
 U:["10001","10001","10001","10001","10001","10001","01110"],
 V:["10001","10001","10001","10001","10001","01010","00100"],
 W:["10001","10001","10001","10101","10101","11011","10001"],
 X:["10001","10001","01010","00100","01010","10001","10001"],
 Y:["10001","10001","01010","00100","00100","00100","00100"],
 Z:["11111","00001","00010","00100","01000","10000","11111"]
};

class Point {
  constructor(x,y,row){
    this.x=x; this.y=y;
    this.tx=x; this.ty=y;
    this.row=row;
    this.delay=0;
    this.active=true;
    this.vy = 0; 
    this.falling = false; 
  }
  
  setTarget(x,y,row,delay=0){
    this.tx=x; this.ty=y;
    this.row=row;
    this.delay=delay;
    if(y > canvas.height + 50){
      this.falling = true;
      this.vy = 0;
    }
  }
  
  atTarget(){
    return Math.abs(this.x-this.tx)<2 && Math.abs(this.y-this.ty)<2;
  }
  
  update(){
    if(!this.active) return;
    if(this.delay>0){ this.delay--; return; }
    if(this.falling){
      this.vy += 0.8; 
      this.y += this.vy;
      return;
    }
    const dx = this.tx - this.x;
    const dy = this.ty - this.y;
    if(Math.abs(dy) > 1){
      this.y += Math.sign(dy) * SPEED;
    } else if(Math.abs(dx) > 1){
      this.x += Math.sign(dx) * SPEED;
    }
  }
  
  draw(){
    if(!this.active) return;
    ctx.beginPath();
    ctx.arc(this.x,this.y,RADIUS,0,Math.PI*2);
    ctx.fillStyle="white";
    ctx.fill();
  }
}

let lettersPoints = [];
let lastWord = "";
let phase = 0;
let phaseTimer = 0;
let targetCache = null;
let loosePoints = [];

function setPhase(p){
  phase = p;
  phaseTimer = 20;
  const names = ["ESPERA","BAJAR A BUFFER","FORMAR 7→0","ESPERAR","RELLENO","LIMPIEZA"];
  phaseBox.textContent = "FASE: " + names[p];
}

function buildTargets(ch, baseX, baseY){
  const m = LETTERS[ch];
  const rows = Array.from({length: MATRIX_ROWS}, ()=>[]);
  if(!m) return rows;
  for(let r=0;r<LETTER_ROWS;r++){
    for(let c=0;c<5;c++){
      if(m[r][c]==="1"){
        rows[r].push({x:baseX+c*CELL,y:baseY+r*CELL,row:r});
      }
    }
  }
  return rows;
}

function buildFirstWord(word){
  word = word.toUpperCase();
  const offsetX = (canvas.width/2)-(word.length*6*CELL/2);
  const offsetY = canvas.height/4;

  lettersPoints = [];

  for(let i=0;i<word.length;i++){
    const ch = word[i];
    const baseX = offsetX + i*6*CELL;
    const baseY = offsetY;
    const targets = buildTargets(ch, baseX, baseY);

    const group = [];
    let delayCount = 0;

    for(let r=0;r<LETTER_ROWS;r++){
      for(let t of targets[r]){
        const px = t.x;
        const py = canvas.height + 40;
        const p = new Point(px, py, r);
        p.setTarget(t.x, t.y, r, delayCount * ROW_DELAY);
        delayCount++;
        group.push(p);
      }
    }
    lettersPoints[i] = group;
  }

  lastWord = word;
  setPhase(0);
}

function reformWord(word){
  word = word.toUpperCase();
  const offsetX = (canvas.width/2)-(word.length*6*CELL/2);
  const offsetY = canvas.height/4;

  targetCache = [];
  const newLetters = [];

  for(let i=0;i<word.length;i++){
    const ch = word[i];
    const baseX = offsetX + i*6*CELL;
    const baseY = offsetY;

    const targetRows = buildTargets(ch, baseX, baseY);
    const oldPoints = lettersPoints[i] || [];

    targetCache.push({ targetRows, oldPoints });
    newLetters.push(oldPoints);
  }

  lettersPoints = newLetters;
  lastWord = word;
  setPhase(1);
}

function allAtTarget(){
  for(let g of lettersPoints){
    for(let p of g){
      if(!p.atTarget()) return false;
    }
  }
  return true;
}

function fillMissingPoints(){
  for(let i=0;i<targetCache.length;i++){
    const { targetRows, oldPoints } = targetCache[i];
    const needed = targetRows.flat().length;
    const have = oldPoints.length;

    if(have < needed){
      const diff = needed - have;
      const targetsFlat = targetRows.flat();
      for(let k=have; k<needed; k++){
        const t = targetsFlat[k];
        if(!t) continue;
        const px = t.x;
        const py = canvas.height + 80;
        const p = new Point(px, py, 13);
        oldPoints.push(p);
      }
    }
  }
}

function applyTargetsAgain(){
  for(let i=0;i<targetCache.length;i++){
    const { targetRows, oldPoints } = targetCache[i];

    const pointsByX = {};
    for(let p of oldPoints){
      const key = Math.round(p.x);
      if(!pointsByX[key]) pointsByX[key] = [];
      pointsByX[key].push(p);
    }

    const targetsByX = {};
    for(let r=0;r<LETTER_ROWS;r++){
      for(let t of targetRows[r]){
        const key = Math.round(t.x);
        if(!targetsByX[key]) targetsByX[key] = [];
        targetsByX[key].push(t);
      }
    }

    for(let key in targetsByX){
      const colTargets = targetsByX[key] || [];
      const colPoints  = pointsByX[key]  || [];

      for(let j=0;j<colTargets.length;j++){
        const t = colTargets[j];
        const p = colPoints[j];
        if(!p) continue;
        p.setTarget(t.x, t.y, t.row, t.row * ROW_DELAY);
      }
    }
  }
}

function cleanLoosePoints(){
  for(let i=0;i<targetCache.length;i++){
    const { targetRows, oldPoints } = targetCache[i];
    const needed = targetRows.flat().length;

    let fallDelay = 0;
    while(oldPoints.length > needed){
      const p = oldPoints.pop();
      p.setTarget(p.x, canvas.height + 200, 13, fallDelay);
      loosePoints.push(p);
      fallDelay += 5;
    }
  }
}

function animate(){
  ctx.clearRect(0,0,canvas.width,canvas.height);

  for(let g of lettersPoints){
    for(let p of g){
      p.update();
      p.draw();
    }
  }

  for(let i=loosePoints.length-1; i>=0; i--){
    const p = loosePoints[i];
    p.update();
    p.draw();
    
    if(p.y > canvas.height + 150){
      loosePoints.splice(i, 1);
    }
  }

  if(phaseTimer>0){
    phaseTimer--;
  } else {
    if(phase===1){
      for(let g of lettersPoints){
        for(let p of g){
          const nr = p.row+7;
          p.setTarget(p.x,(canvas.height/4)+nr*CELL,nr,(LETTER_ROWS-p.row)*ROW_DELAY);
        }
      }
      setPhase(2);
    } else if(phase===2 && allAtTarget()){
      for(let i=0;i<targetCache.length;i++){
        const {targetRows,oldPoints} = targetCache[i];
        let pool=[...oldPoints];
        let idx=0;
        for(let r=0;r<LETTER_ROWS;r++){
          for(let t of targetRows[r]){
            const p=pool[idx++];
            if(!p) continue;
            p.setTarget(t.x,t.y,r,r*ROW_DELAY);
          }
        }
      }
      setPhase(3);
    } else if(phase===3 && allAtTarget()){
      setPhase(4);
    } else if(phase===4 && allAtTarget()){
      cleanLoosePoints();
      setPhase(5);
    } else if(phase===5){
      fillMissingPoints();
      applyTargetsAgain();
      setPhase(0);
    }
  }

  requestAnimationFrame(animate);
}

btn.onclick = ()=>{
  const w = wordInput.value.trim();
  if(!w) return;
  if(lastWord==="") buildFirstWord(w);
  else reformWord(w);
};

animate();
