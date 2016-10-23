function Player (game, imageKey, x, y)
{
  this.game = game;
  this.sprite = game.add.sprite(x, y, imageKey);

  this.controls = getKeys(game, imageKey);

  //physics setup
  game.physics.arcade.enable(this.sprite);

  this.sprite.body.bounce.y = 0.2;
  this.sprite.body.gravity.y = 900;
  this.sprite.body.collideWorldBounds = true;

  this.sprite.anchor.setTo(.5, 0);
}

Player.prototype.update = function()
{
    //  Reset the sprite velocity (movement)
    this.sprite.body.velocity.x = 0;

    if (this.controls.left.isDown)
    {
        //  Move to the left
        this.sprite.body.velocity.x = -150;
        this.sprite.scale.x = -1;
    }
    else if (this.controls.right.isDown)
    {
        //  Move to the right
        this.sprite.body.velocity.x = 150;
        this.sprite.scale.x = 1;
    }
    else
    {
    }
    //  Allow the player to jump if they are touching the ground.
    if (this.controls.up.isDown && (this.sprite.body.blocked.down || this.sprite.body.touching.down))
    {
        this.sprite.body.velocity.y = -350;
    }

}

function getKeys(game, imageKey)
{
  if (imageKey == "kevin")
  {
    var keys = {
      up: game.input.keyboard.addKey(Phaser.Keyboard.UP),
      left: game.input.keyboard.addKey(Phaser.Keyboard.LEFT),
      right: game.input.keyboard.addKey(Phaser.Keyboard.RIGHT),
    };
    return keys;
  }
  else (imageKey == "zaq")
  {
    var keys = {
      up: game.input.keyboard.addKey(Phaser.Keyboard.W),
      left: game.input.keyboard.addKey(Phaser.Keyboard.A),
      right: game.input.keyboard.addKey(Phaser.Keyboard.D),
    };
    return keys;
  }
}
