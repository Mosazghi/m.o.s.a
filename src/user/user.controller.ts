import {
  Body,
  Controller,
  Get,
  HttpStatus,
  Next,
  Post,
  Request,
  Res,
  Response,
  UseGuards,
} from '@nestjs/common';
import { LocalAuthGuard } from 'src/auth/local-auth.guard';
import { CreateUserDto } from './dto/create-user.dto';
import { UserService } from './user.service';

@Controller('user')
export class UserController {
  constructor(private readonly userService: UserService) {}

  @Post('/register')
  async createUser(@Res() res, @Body() createUserDto: CreateUserDto) {
    const newUser = this.userService.createUser(createUserDto);
    console.log('New User:', newUser);
    if ((await newUser) !== null) {
      res.redirect('/');
    } else {
      res.status(HttpStatus.BAD_REQUEST).send('Bruker finnes allerde!');
    }
  }

  @UseGuards(LocalAuthGuard)
  @Post('/login')
  async login(@Request() req, @Response() res, @Next() next) {
    console.log('LOGGED IN', req.isAuthenticated());
    if (req) {
      res.redirect('/dashboard');
    } else res.send('/'); // <- TODO: faktiskt redirecte tilbake til login (hvis bruker ikke finnes)
  }

  @Get('/logut')
  async logout(@Request() req, @Response() res, @Next() next) {
    req.logout((err) => {
      if (err) {
        return next(err);
      }
      console.log('LOGGET UT', req.isAuthenticated());
      res.redirect('/');
    });
  }
}
