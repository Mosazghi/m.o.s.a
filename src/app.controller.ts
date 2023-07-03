import {
  Controller,
  Get,
  Render,
  Request,
  UseFilters,
  UseGuards,
} from '@nestjs/common';
import { AppService } from './app.service';
import { AuthenticatedGuard } from './auth/authenticated.guard';
import { ViewAuthFilter } from './auth/redirect-to-login';
import { UserService } from './user/user.service';
@Controller()
export class AppController {
  constructor(
    private readonly appService: AppService,
    private readonly userService: UserService,
  ) {}

  @Get()
  @Render('index')
  root() {}

  @UseGuards(AuthenticatedGuard)
  @Get('/dashboard')
  @UseFilters(ViewAuthFilter)
  @Render('dashboard')
  async dash(@Request() req) {
    console.log('userID: ', req.session.passport.user);
    const user = await this.userService.findById(req.session.passport.user);
    console.log('userinfo: ', user.username, user.password);
    return { username: user.username, pass: user.password }; // se dashboard.hbs
  }

  @Get('/register')
  @Render('register')
  reg() {}
}
